//
// Process_WINCE.h
//
// $Id: //poco/1.4/Foundation/include/Poco/Process_WINCE.h#2 $
//
// Library: Foundation
// Package: Processes
// Module:  Process
//
// Definition of the ProcessImpl class for WIN32.
//
// Copyright (c) 2004-2010, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_Process_WINCE_INCLUDED
#define Foundation_Process_WINCE_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/RefCountedObject.h"
#include <vector>
#include "Poco/UnWindows.h"


namespace Poco {


class Pipe;


class Foundation_API ProcessHandleImpl: public RefCountedObject
{
public:
	ProcessHandleImpl(HANDLE _hProcess, UInt32 pid);
	~ProcessHandleImpl();
	
	UInt32 id() const;
	HANDLE process() const;
	int wait() const;
	
private:
	HANDLE _hProcess;
	UInt32 _pid;

	ProcessHandleImpl(const ProcessHandleImpl&);
	ProcessHandleImpl& operator = (const ProcessHandleImpl&);
};


class Foundation_API ProcessImpl
{
public:
	typedef UInt32 PIDImpl;
	typedef std::vector<std::string> ArgsImpl;
	
	static PIDImpl idImpl();
	static void timesImpl(long& userTime, long& kernelTime);
	static ProcessHandleImpl* launchImpl(const std::string& command, const ArgsImpl& args, Pipe* inPipe, Pipe* outPipe, Pipe* errPipe);		
	static void killImpl(const ProcessHandleImpl& handle);
	static void killImpl(PIDImpl pid);
	static void requestTerminationImpl(PIDImpl pid);
	static std::string terminationEventName(PIDImpl pid);
};


} // namespace Poco


#endif // Foundation_Process_WINCE_INCLUDED
