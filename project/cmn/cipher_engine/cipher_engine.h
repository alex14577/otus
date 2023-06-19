#pragma once

#include <openssl/rsa.h>

#include <string>

class CipherEngine
{
public:
     ~CipherEngine();
     bool Init();
     std::string EncryptMessage(const std::string& message);
     std::string DecryptMessage(const std::string& message);

     std::string GetPubKey() const;
     bool AddOtherPubKey(const std::string& key);

private:
     EVP_PKEY* key_ = nullptr;
     EVP_PKEY* publicKeyOther_ = nullptr;
          
};