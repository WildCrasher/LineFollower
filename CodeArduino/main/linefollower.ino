int tab_czujnikow[5] = {5,4,3,2,1};
int czujniki[5] = {0};
int wagi[5]={-30,-10,0,10,30};
int poprzednie[5] = {0};
int index=0;
int skrety=0;

int sprawdz_pomiary()
{
  int a=0;
  int b=0;
  for(int i=0; i<5;i++)
  {
    if(poprzednie[i]<-5)
    {
      a++;
    }
    else if(poprzednie[i]>5)
    {
      b++;
    }
  }
  if(a>=3)
    return -5;
  else if(b>=3)
    return 5;
  else 
    return 0;
}

void prawy_silnik_przod()
{
    digitalWrite(EN_22,HIGH);//prawy
    digitalWrite(EN_21,LOW);
}
void prawy_silnik_tyl()
{
    digitalWrite(EN_22,LOW);//prawy
    digitalWrite(EN_21,HIGH);
}
void lewy_silnik_przod()
{
    digitalWrite(EN_12,HIGH);
    digitalWrite(EN_11,LOW);
}
void lewy_silnik_tyl()
{
    digitalWrite(EN_12,LOW);
    digitalWrite(EN_11,HIGH);
}

void PWM(int lewy, int prawy)
{
        if(lewy >= 0)
        {
            if(lewy>255)
                lewy = 255;
            digitalWrite(EN_12,HIGH);
            digitalWrite(EN_11,LOW);
        }
        else
        {
            if(lewy<-255)
                lewy = -255;
            digitalWrite(EN_12,LOW);
            digitalWrite(EN_11,HIGH);
        }

        if(prawy >= 0)
        {
            if(prawy>255)
                prawy = 255;
            digitalWrite(EN_22,HIGH);
            digitalWrite(EN_21,LOW);
        }
        else
        {
            if(prawy<-255)
                prawy = -255;
            digitalWrite(EN_22,LOW);
            digitalWrite(EN_21,HIGH);
        }
        analogWrite(PWM1,abs(lewy));
        analogWrite(PWM2,abs(prawy));
}

bool wszystkie_czujniki()
{
  int a=0;
  for(int i=0;i<5;i++)
  {
    if(czujniki[i]==1)
      a++;
  }
  if(a==5)
  return true;
  else
  return false;
}

void avoid()
{
  const int czas_skretu=500;
  const int czas_po_prostej=900;
  digitalWrite(PWM1,255);
  digitalWrite(PWM2,255);
  
  prawy_silnik_tyl();
  lewy_silnik_przod();
  delay(czas_skretu); 
   
  prawy_silnik_przod();
  delay(czas_po_prostej);
  
  lewy_silnik_tyl();
  delay(czas_skretu);
  
  lewy_silnik_przod();
  delay(1200);
  
  lewy_silnik_tyl();
  delay(325);
  
  lewy_silnik_przod();
  delay(500);

  while(true)
  {
    czytaj_adc();
    if(czujniki[4]==1)
    {
      prawy_silnik_tyl();
      delay(350);
      prawy_silnik_przod();
      break;
    }
    else if(czujniki[0]==1)
    {
      delay(100);
      prawy_silnik_tyl();
      delay(200);
      prawy_silnik_przod();
      break;
    }
    delay(10);
  }
}

void czytaj_adc()
{
    if( analogRead( CZ_1 ) > 600 )
      czujniki[0] = 1;
    else
      czujniki[0] = 0;
      
    if( analogRead( CZ_2 ) > 600 )
      czujniki[1] = 1;
    else
      czujniki[1] = 0;
      
    if( analogRead( CZ_3 ) > 600 )
      czujniki[2] = 1;
    else
      czujniki[2] = 0;

    if( analogRead( CZ_4 ) > 600 )
      czujniki[3] = 1;
    else
      czujniki[3] = 0;

    if( analogRead( CZ_5 ) > 600 )
      czujniki[4] = 1;
    else
      czujniki[4] = 0;
}

int PD() 
{ 
    //zmienna blad zawiera aktualny wynik fukcji licz_blad() 
    int rozniczka = blad - pop_blad; 
    pop_blad = blad; 
    return Kp*blad + Kd*rozniczka; 
}

int licz_blad()
{
  int err = 0;            // wartoÄąâ€śÄ‚Â¦ bĂ‚Ĺ‚Ä‚Ĺždu
  int ilosc = 0;            // iloÄąâ€śÄ‚Â¦ czujnikÄ‚Ĺ‚w z wykrytĂ‚Ä… liniĂ‚Ä…
  for(int i=0; i<5; i++)
  {
    err += czujniki[i]*wagi[i];  // wagi kolejnych czujnikÄ‚Ĺ‚w (dla i z zakresu [0;7]): -30, -20, -10, 0, 10, 20, 30
    ilosc += czujniki[i];     // czujniki[i] ma wartoÄąâ€śÄ‚Â¦ 1/0
  }
    if( ilosc != 0 )
    {
        err /= ilosc;
        if(index>=5)
        index=0;
        poprzednie[index++]=err;
    }
    else
    {
        if(sprawdz_pomiary()==-5)
		    {
          err=-80;
		    }
        else if(sprawdz_pomiary()==5)
		    {
          err=80;
		    }
       else
          err=0;
    }
  
  return err;
}


