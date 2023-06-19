#pragma once

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/JSONException.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <ostream>

class Message
{
public:
     Message(const std::string& sender, const std::string& text);

     Message(const std::string jsonString);

     const std::string GetSender() const;

     const std::string GetText() const;

     std::string ToString() const;

     const std::string& GetErr() const;

private:
     struct Fileds
     {
          static constexpr std::string_view sender = "sender";
          static constexpr std::string_view text = "text"; 
     };     
     std::string err;
     Poco::JSON::Object::Ptr jsonObject_ = Poco::makeShared<Poco::JSON::Object>();
};