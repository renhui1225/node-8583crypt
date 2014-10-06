#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <cstring>
#include "crypt.h"


using namespace v8;
using namespace node;

Handle<Value>
ErrorException(const char *msg)
{
    HandleScope scope;
    return Exception::Error(String::New(msg));
}

Handle<Value>
VException(const char *msg)
{
    HandleScope scope;
    return ThrowException(ErrorException(msg));
}


Handle<Value>
encrypt(const Arguments &args)
{
	HandleScope scope;
	
    if(args.Length() != 2)
    {
        return VException("Three arguments required - <Data> and <encrypt key>");
    }
    if (!Buffer::HasInstance(args[0]))
    {
        return VException("<data> must be a buffer.");
    }
    if (!Buffer::HasInstance(args[1]))
    {
        return VException("<encryption key> must be a buffer.");
    }
	Local<Object> data_obj = args[0]->ToObject();
    size_t dlen = Buffer::Length(data_obj);

/*
	if (dlen % 8 != 0)
    {
        return VException("<data> length must be multiple of 8.");
    }
  */

	Local<Object> key_obj = args[1]->ToObject();
	size_t klen = Buffer::Length(key_obj);

	if((klen != 8 ) && (klen != 16))
	{
		 return VException("<encrypt key> length must be 8 or 16.");
	}

    Buffer *retbuf = Buffer::New(dlen);
    unsigned char *ptr = (unsigned char *) Buffer::Data(retbuf);

	for (int j = 0; j < dlen; j += 8)
    {
		if(klen == 8)
		{
			mydes(ptr + j, (unsigned char *)(Buffer::Data(data_obj) + j), (unsigned char *)Buffer::Data(key_obj), 0);
		}
		else
		{
			mydes3(ptr + j, (unsigned char *)(Buffer::Data(data_obj) + j), (unsigned char *)Buffer::Data(key_obj), 0);
		}
	}

    return scope.Close(retbuf->handle_);
}

Handle<Value>
decrypt(const Arguments &args)
{
	HandleScope scope;
	
    if(args.Length() != 2)
    {
        return VException("Three arguments required - <Data> and <encrypt key>");
    }
    if (!Buffer::HasInstance(args[0]))
    {
        return VException("<data> must be a buffer.");
    }
    if (!Buffer::HasInstance(args[1]))
    {
        return VException("<encryption key> must be a buffer.");
    }
	Local<Object> data_obj = args[0]->ToObject();
    size_t dlen = Buffer::Length(data_obj);

	if (dlen % 8 != 0)
    {
        return VException("<data> length must be multiple of 8.");
    }

	Local<Object> key_obj = args[1]->ToObject();
	size_t klen = Buffer::Length(key_obj);

	if((klen != 8 ) && (klen != 16))
	{
		 return VException("<encrypt key> length must be 8 or 16.");
	}

    Buffer *retbuf = Buffer::New(dlen);
    unsigned char *ptr = (unsigned char *) Buffer::Data(retbuf);

	for (int j = 0; j < dlen; j += 8)
    {
		if(klen == 8)
		{
			mydes(ptr + j, (unsigned char *)(Buffer::Data(data_obj) + j), (unsigned char *)Buffer::Data(key_obj), 1);
		}
		else
		{
			mydes3(ptr + j, (unsigned char *)(Buffer::Data(data_obj) + j), (unsigned char *)Buffer::Data(key_obj), 1);
		}
	}

    return scope.Close(retbuf->handle_);
}


Handle<Value>
calcmac(const Arguments &args)
{
	HandleScope scope;
	
    if(args.Length() != 2)
    {
        return VException("Three arguments required - <Data> and <encrypt key>");
    }
    if (!Buffer::HasInstance(args[0]))
    {
        return VException("<data> must be a buffer.");
    }
    if (!Buffer::HasInstance(args[1]))
    {
        return VException("<encryption key> must be a buffer.");
    }
	  Local<Object> data_obj = args[0]->ToObject();
    size_t dlen = Buffer::Length(data_obj);

	Local<Object> key_obj = args[1]->ToObject();
	size_t klen = Buffer::Length(key_obj);

	if((klen != 8 ) && (klen != 16))
	{
		 return VException("<encrypt key> length must be 8 or 16.");
	}

    Buffer *retbuf = Buffer::New(8);
    unsigned char *ptr = (unsigned char *) Buffer::Data(retbuf);
	CalcMAC_ECB(ptr, (unsigned char *)Buffer::Data(data_obj), dlen,  (unsigned char *)Buffer::Data(key_obj), klen);
    return scope.Close(retbuf->handle_);
}


Handle<Value>
encryptpin(const Arguments &args)
{
	HandleScope scope;
	
    if(args.Length() != 3)
    {
        return VException("Three arguments required - <plain> <pan> and <encrypt key>");
    }

    if (!args[0]->IsString())
        return VException("<plain> must be a string.");

    if (!args[1]->IsString())
        return VException("<pan> must be a string.");

    if (!Buffer::HasInstance(args[2]))
    {
        return VException("<encryption key> must be a buffer.");
    }


	Local<Object> key_obj = args[2]->ToObject();
	size_t klen = Buffer::Length(key_obj);
	if((klen != 8 ) && (klen != 16))
	{
		 return VException("<encrypt key> length must be 8 or 16.");
	}

    Buffer *retbuf = Buffer::New(8);
    unsigned char *ptr = (unsigned char *) Buffer::Data(retbuf);
	
    String::AsciiValue plain(args[0]->ToString());
    String::AsciiValue pan(args[1]->ToString());

	EncryptPINExt(ptr,(char *)*plain, (char *)*pan, (unsigned char *)Buffer::Data(key_obj), klen);
	
    return scope.Close(retbuf->handle_);
}



extern "C" void init (Handle<Object> target)
{
    HandleScope scope;
    target->Set(String::New("encrypt"), FunctionTemplate::New(encrypt)->GetFunction());
    target->Set(String::New("decrypt"), FunctionTemplate::New(decrypt)->GetFunction());
    target->Set(String::New("calcmac"), FunctionTemplate::New(calcmac)->GetFunction());
    target->Set(String::New("encryptpin"), FunctionTemplate::New(encryptpin)->GetFunction());
}

NODE_MODULE(poscrypt, init);