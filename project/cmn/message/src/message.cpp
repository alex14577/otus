#include <cmn/message/message.h>

Message::Message(const std::string& sender, const std::string& text)
{
     try
     {
          jsonObject_->set(Fileds::text.data(), text);
          jsonObject_->set(Fileds::sender.data(), sender);
     }
     catch(const Poco::JSON::JSONException& e)
     {
          err = e.displayText();
     }
}

Message::Message(const std::string jsonString)
{
     try
     {
          Poco::JSON::Parser parser;
          Poco::Dynamic::Var result = parser.parse(jsonString);
          jsonObject_ = result.extract<Poco::JSON::Object::Ptr>();
     }
     catch(const Poco::JSON::JSONException& e)
     {
          err = e.displayText();
     }          
}

const std::string Message::GetSender() const
{
     if(!err.empty())
     {
          return {};
     }
     if(jsonObject_->has(Fileds::sender.data()))
     {
          return jsonObject_->get(Fileds::sender.data()).toString();
     }
     return {};
}

const std::string Message::GetText() const
{
     if(!err.empty())
     {
          return {};
     }
     if(jsonObject_->has(Fileds::text.data()))
     {
          return jsonObject_->get(Fileds::text.data()).toString();
     }
     return {};
}

std::string Message::ToString() const
{
     if(!err.empty())
     {
          return {};
     }
     std::stringstream res;
     Poco::JSON::Stringifier::stringify(jsonObject_, res);
     return res.str();          
}

const std::string& Message::GetErr() const
{
     return err;
}
