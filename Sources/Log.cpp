#include "stdafx.h"
#include "Log.h"
#include "EngineBase.h"

namespace Tuxis
{
	Log* Log::Instance = NULL;
	bool Log::ConsoleLoging = true;
	
	Log::Log()
	{
		
		
		if(Instance==NULL)
		{
			FileName = "Log.txt";
			Instance = this;
			Instance->Init();
		}
		else
		{
			Warning("Log::Log: Log already exist");
		}
	}
	
	Log::~Log()
	{
		Release();
	}

	void Log::Release()
	{
		Separator();
		Info( "Stop logging" );
		Separator();
		mFile.close();
		Instance=NULL;
	}
	

	void Log::EnableConsoleLoging(bool IsIt)
	{
		ConsoleLoging = IsIt;
	}

	void Log::Init()
	{
		mFile.open( FileName , ios_base::out );
		if(!mFile.fail())
		{
			WriteText( "Tuxis Log System\n" );
#ifdef _DEBUG
			WriteText("Debug mode\n");
#else
			WriteText("Release mode\n");
#endif
			Separator();
			Info("Start logging");
			Separator();
		}
	}
	
	
	void Log::Info( const char* pMessage )
	{
		string Message = pMessage;
		if( Instance )
		{
			Message.insert(0,"INFO: ");
			Message.append("\n");
			Instance->WriteAll(Message.c_str());
		}
	}
	
	
	void Log::WriteText( const char* Message )
	{
		if( Instance )
		{
			Instance->WriteAll(Message);
		}
	}
	
	
	void Log::Separator()
	{
		if( Instance )
		{
			string Message="-------------------------------------------------------------------------------\n" ;
			Instance->mFile.write( Message.c_str(), Message.size() );
			if(ConsoleLoging) cout<<Message.c_str();
		}
	}
	
	
	void Log::Error(  const char* pMessage )
	{
		string Message = pMessage;

		if( Instance )
		{
			Message.insert(0,"ERROR: ");
			Message.append("\n");
			Instance->WriteAll(Message.c_str());
			Instance->Release();
		}
			MessageBoxA(0,Message.c_str(),"Error",0);
			throw Message.c_str();
	}
	
	
	void Log::Warning( const char* pMessage )
	{
		string Message = pMessage;
		if( Instance )
		{
			Message.insert(0,"WARNING: ");
			Message.append("\n");
			Instance->WriteAll(Message.c_str());
		}
	}
	
	
	void Log::Success( const char* pMessage )
	{
		string Message = pMessage;
		if( Instance )
		{
			Message.insert(0,"SUCCESS: ");
			Message.append("\n");
			Instance->WriteAll(Message.c_str());
		}
	}


	bool Log::operator ! ()
	{
		return Instance==nullptr;
	}


	Log& Log::operator<<( int i )
	{
		if(Instance)
		{
			string Message = IntToString(i);
			Instance->WriteAll(Message.c_str());
		}
		return *this;
	}


	Log& Log::operator<<( float i )
	{
		if(Instance)
		{
			string Message = FloatToString(i);
			Instance->WriteAll(Message.c_str());
		}
		
		return *this;
	}


	Log& Log::operator<<( const char* Message )
	{
		if(Instance)
		{
			Instance->WriteAll(Message);
		}
		return *this;
	}


	void Log::WriteAll( const char* ResultMessage )
	{
		if(mFile.is_open())
		{
			mFile.write( ResultMessage, strlen(ResultMessage) );
			mFile.flush();
		}
		if(ConsoleLoging) cout<<ResultMessage;
	}


}
