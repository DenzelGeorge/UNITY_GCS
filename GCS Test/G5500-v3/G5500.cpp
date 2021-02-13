#include "G5500.h"
#include "Arduino.h"

G5500::G5500() //constructor; basically, just set up the pins, turn them off
{
  pinMode(_upPin, OUTPUT);
  pinMode(_downPin, OUTPUT);
  pinMode(_eastPin, OUTPUT);
  pinMode(_westPin, OUTPUT);
  
  digitalWrite(_upPin, LOW);
  digitalWrite(_downPin, LOW);
  digitalWrite(_eastPin, LOW);
  digitalWrite(_westPin, LOW);
}

void G5500::setAzEl (int azimuth, int elevation)
{
  int azADC = (float(azimuth)/_azRes)+0.5+_zeroAzPoint;
  int elADC = (float(elevation) / _elRes)+0.5+_zeroElPoint;
  
  if(azADC > _maxAzPoint) azADC = _maxAzPoint;
  if(azADC < _zeroAzPoint) azADC = _zeroAzPoint;
  if(elADC > _maxElPoint) elADC = _maxElPoint;
  if(elADC < _zeroElPoint) elADC = _zeroElPoint;
 
  int azInd = G5500::getAz();
  if(abs(azADC - azInd) <= _azDeadZone) return;
  int elInd = G5500::getEl();
  if(abs(elADC - elInd) <= _elDeadZone) return;

  while((azInd != azADC) || (elInd != elADC))
  {
    if((azInd < azADC) && (elInd < elADC))
    {
      digitalWrite(_westPin, LOW);
      digitalWrite(_eastPin, HIGH);
      digitalWrite(_downPin, LOW);
      digitalWrite(_upPin, HIGH);
    }
    else if((azInd > azADC) && (elInd < elADC))
    {
      digitalWrite(_eastPin, LOW);
      digitalWrite(_westPin, HIGH);
      digitalWrite(_downPin, LOW);
      digitalWrite(_upPin, HIGH);
    }
    else if((azInd < azADC) && (elInd > elADC)) 
    {
      digitalWrite(_downPin, LOW);
      digitalWrite(_upPin, HIGH);
    }
    else if ((azInd > azADC) && (elInd > elADC))
    {
      digitalWrite(_upPin, LOW);
      digitalWrite(_downPin, HIGH);
    }
    elInd = G5500::getEl();
    azInd = G5500::getAz();
  }

  digitalWrite(_upPin, LOW);
  digitalWrite(_downPin, LOW);
  digitalWrite(_eastPin, LOW);
  digitalWrite(_westPin, LOW);
}

void G5500::setAz(int azimuth)
{
  int azADC = (float(azimuth)/_azRes)+0.5+_zeroAzPoint;
  if(azADC > _maxAzPoint) azADC = _maxAzPoint;
  if(azADC < _zeroAzPoint) azADC = _zeroAzPoint;
  int azInd = G5500::getAz();
  if(abs(azADC - azInd) <= _azDeadZone) return;
  while(azInd != azADC)
  {
    if(azInd < azADC) 
    {
      digitalWrite(_westPin, LOW);
      digitalWrite(_eastPin, HIGH);
    }
    else if(azInd > azADC) 
    {
      digitalWrite(_eastPin, LOW);
      digitalWrite(_westPin, HIGH);
    }
    azInd = G5500::getAz();
  }
  digitalWrite(_eastPin, LOW);
  digitalWrite(_westPin, LOW);
}

void G5500::setEl(int elevation)
{
  int elADC = (float(elevation) / _elRes)+0.5+_zeroElPoint;
  if(elADC > _maxElPoint) elADC = _maxElPoint;
  if(elADC < _zeroElPoint) elADC = _zeroElPoint;
  int elInd = G5500::getEl();
  if(abs(elADC - elInd) <= _elDeadZone) return;
  while(elInd != elADC)
  {
    if(elInd < elADC)
    {
      digitalWrite(_downPin, LOW);
      digitalWrite(_upPin, HIGH);
    }
    else if (elInd > elADC)
    {
      digitalWrite(_upPin, LOW);
      digitalWrite(_downPin, HIGH);
    }
    elInd = G5500::getEl();
  }
  digitalWrite(_upPin, LOW);
  digitalWrite(_downPin, LOW);
}

int G5500::getAz()
{
  return analogRead(_azSensePin);
}

int G5500::getEl()
{
  return analogRead(_elSensePin);
}

int G5500::getAzDegrees()
{
  int azInd = G5500::getAz();
  int azimuth = float(azInd - _zeroAzPoint) * _azRes;
  if (azimuth < 0) azimuth = 0;
  else if(azimuth > 450) azimuth = 450;
  return azimuth;
}

int G5500::getElDegrees()
{
  int elInd = G5500::getEl();
  int elevation = float(elInd - _zeroElPoint) * _elRes;
  if (elevation < 0) elevation = 0;
  else if(elevation > 180) elevation = 180;
  return elevation;
}