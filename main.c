#include <main.h>


/*m1 d�necek s3 butonuna bas�l�nca band�n sonuna gelmi� demektir m2 ba�ta onu bekliyor kabul edelim 
m5 60 derece d�nerek a�a�� inecek ve kavrama i�in m4 90 derece d�necek
m5 tekrar 60 derece d�nerek yukar� ��kacak 
sonra m2 90 derece d�necek ve di�re banda gelecek
sonra m5 60 derece a�a�� inecek ve m4 90 derece d�nerek kutuyu b�rakacak
sonra s4 butonuna bas�lana kadar m3 band� hareket edecek
sonra m5 tekrar 60 derece yukar� kalkacak ve m2 tekrar 90 derece d�nerek eski yerine gelecek
ve sistem tekrar edecek*/

//s3 Butonu A0 a ba�l�
//s4 butonu A1 e ba�l�

//fonksiyonlara ay�r kafan rahat olsun
int adim[] = {0b00000001,0b00000011,0b00000010,0b00000110,0b00000100,0b00001100,0b00001000,0b00001001};//0. pinden 
int adim2[] = {0b00010000,0b00110000,0b00100000,0b01100000,0b01000000,0b11000000,0b10000000,0b10010000};//bunun bitleri kayd�r�larak di�er step motora uydurulacak
//0b00000101 ileri  Dc motor 3 bit kayd�r�lacak
int mbirIleri = 0b00000101;
int mUcIleri =  0b00000101 << 3;
int dirsekAdimBuyuklugu = 40,sayac2;
int omuzAdimBuyuklugu = 60;
int kapanmaAcisi = 60;

void omuzIleri(){
      for(int sayac = 0 ; sayac < omuzAdimBuyuklugu; sayac++){
        sayac2 = sayac%8;
        output_d(adim[sayac2]);
       delay_ms(50);
      }
}
void omuzGeri(){
      for(int sayac = omuzAdimBuyuklugu ; sayac > 0 ; sayac--){
        sayac2 = sayac%8;
        output_d(adim[sayac2]);
       delay_ms(50);
      }

}
void m1BandiCalistir(){
   output_b(mbirIleri);
}
void BandiDurdur(){
   output_b(0x00);
}
void m3BandiCalistir(){
   output_b(mUcIleri);
}
void dirsekAsagi(){
   for(int sayac = 0 ; sayac < dirsekAdimBuyuklugu; sayac++){
        sayac2 = sayac%8;
        output_c(adim[sayac2]);
       delay_ms(50);
      }

}
void dirsekYukari(){
    for(int sayac = dirsekAdimBuyuklugu ; sayac > 0 ; sayac--){
        sayac2 = sayac%8;
        output_c(adim[sayac2]);
       delay_ms(50);
      }
}
void kistir(){
  for(int sayac = 0 ; sayac < dirsekAdimBuyuklugu; sayac++){
        sayac2 = sayac%8;
        output_c(adim2[sayac2]);
       delay_ms(50);
      }
   
}
void kistirma(){
    for(int sayac = dirsekAdimBuyuklugu ; sayac > 0 ; sayac--){
        sayac2 = sayac%8;
        output_c(adim2[sayac2]);
       delay_ms(50);
      }

}


void main()
{
set_tris_a(0xff);
set_tris_b(0x00);
set_tris_c(0x00);
set_tris_d(0x00);
output_b(0x00);
output_c(0x00);
output_d(0x00);
   


   while(TRUE)
   {
      m1BandiCalistir();
      while(input(pin_A0) == 0);//sens�r kutuyu alg�layana kadar bekle
      delay_us(200);//alg�land�
      BandiDurdur();
      dirsekAsagi();
      kistir();
      dirsekYukari();
      omuzIleri();
      dirsekAsagi();
      kistirma();
      
      dirsekYukari();
      m3BandiCalistir();
      omuzGeri();
      while(input(pin_A1) == 0);
      delay_us(200);//alg�land�
      BandiDurdur();
      
      
    
   }
}


