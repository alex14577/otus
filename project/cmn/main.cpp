#include <iostream>

#include <cmn/cipher_engine/cipher_engine.h>

int main() {
     CipherEngine c1;
     CipherEngine c2;

     c1.Init();
     c2.Init();

     auto pKey1 = c1.GetPubKey();
     auto pKey2 = c2.GetPubKey();

     std::cout << pKey1 << std::endl;
     std::cout << pKey2 << std::endl;

     c1.AddOtherPubKey(pKey2);
     c2.AddOtherPubKey(pKey1);

     std::string mes = "Hello World";

     auto enc = c2.EncryptMessage(mes);
     std::cout << enc << std::endl;
     auto dec = c1.DecryptMessage(enc);

     std::cout << dec << std::endl;

     if(mes == dec)
     {
          std::cout << "Success" << std::endl;
     }

     return 0;
}
