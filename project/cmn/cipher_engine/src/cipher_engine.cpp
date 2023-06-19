#include <cmn/cipher_engine/cipher_engine.h>

#include <openssl/pem.h>
#include <openssl/err.h>

#include <memory>
#include <vector>

#include <iostream>

namespace
{
std::string ConvertEvpToString(EVP_PKEY* key)
{
     char* publicKeyData = nullptr;
     std::shared_ptr<BIO> publicKeyBio(BIO_new(BIO_s_mem()), BIO_free);
     PEM_write_bio_PUBKEY(publicKeyBio.get(), key);
     long publicKeySize = BIO_get_mem_data(publicKeyBio.get(), &publicKeyData);
     return std::string(publicKeyData, publicKeySize);
}

EVP_PKEY* ConvertEvpFromString(const std::string& key)
{
     std::shared_ptr<BIO> bio(BIO_new_mem_buf(reinterpret_cast<const unsigned char*>(key.c_str()), key.size()), BIO_free);
     return PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr);
}
}

CipherEngine::~CipherEngine()
{
     EVP_PKEY_free(key_);
     EVP_PKEY_free(publicKeyOther_);
}

EVP_PKEY* GenKey()
{
     auto key = EVP_RSA_gen(2048);
     return key;
}

bool CipherEngine::Init()
{     
     key_ = GenKey();
     return key_ != nullptr;
}

std::string CipherEngine::EncryptMessage(const std::string& message)
{
     if(!publicKeyOther_)
     {
          throw std::runtime_error("No other pulic key to encrypt");
     }
     std::shared_ptr<EVP_PKEY_CTX> ctx(EVP_PKEY_CTX_new(publicKeyOther_, nullptr), EVP_PKEY_CTX_free);
     if (!ctx) 
     {
          return "";
     }
     if (EVP_PKEY_encrypt_init(ctx.get()) <= 0) 
     {
          return "";
     }

     size_t encryptedSize = 0;
     if (EVP_PKEY_encrypt(ctx.get(), nullptr, &encryptedSize, 
          reinterpret_cast<const unsigned char*>(message.data()), 
          message.size()) <= 0) 
     {
          std::cerr << ERR_error_string(ERR_get_error(), NULL) << std::endl;
          return "";
     }

     std::vector<unsigned char> encrypted(encryptedSize);
     if (EVP_PKEY_encrypt(ctx.get(), encrypted.data(), &encryptedSize, 
          reinterpret_cast<const unsigned char*>(message.data()), 
          message.size()) <= 0) 
     {
          std::cerr << ERR_error_string(ERR_get_error(), NULL) << std::endl;
          return "";
     }
     
     return std::string(reinterpret_cast<char*>(encrypted.data()), encryptedSize);
}

std::string CipherEngine::DecryptMessage(const std::string& encryptedMessage)
{
     if(!key_)
     {
          throw std::runtime_error("No private key to decrypt");
     }
     std::shared_ptr<EVP_PKEY_CTX> ctx(EVP_PKEY_CTX_new(key_, nullptr), EVP_PKEY_CTX_free);
     if (!ctx) 
     {
          return "";
     }

     if (EVP_PKEY_decrypt_init(ctx.get()) <= 0) 
     {
          return "";
     }

     size_t decryptedSize = 0;
     if (EVP_PKEY_decrypt(ctx.get(), nullptr, &decryptedSize, 
                              reinterpret_cast<const unsigned char*>(encryptedMessage.data()), 
                              encryptedMessage.size()) <= 0) 
     {
          std::cerr << ERR_error_string(ERR_get_error(), NULL) << std::endl;
          return "";
     }    

     std::vector<unsigned char> decrypted(decryptedSize);
     if (EVP_PKEY_decrypt(ctx.get(), decrypted.data(), &decryptedSize,
                              reinterpret_cast<const unsigned char*>(encryptedMessage.data()), 
                              encryptedMessage.size()) <= 0) 
     {
          std::cerr << ERR_error_string(ERR_get_error(), NULL) << std::endl;
          return "";
     }

     return std::string(reinterpret_cast<char*>(decrypted.data()), decryptedSize);
}

std::string CipherEngine::GetPubKey() const
{
     return ConvertEvpToString(key_);
}

bool CipherEngine::AddOtherPubKey(const std::string& key)
{
     publicKeyOther_ = ConvertEvpFromString(key);
     if(publicKeyOther_)
     {
          return true;
     }
     return false;
}
