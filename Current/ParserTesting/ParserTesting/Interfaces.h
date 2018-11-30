#pragma once

#include "Constants.h"

struct Command;
struct Field;

// Base public interface for the command object
struct ICommand {
    virtual ~ICommand()
    {
    }

    virtual const char*		Name() const = 0;
    virtual unsigned int	Index() const = 0;
};

struct IPCOMPData {
    virtual ~IPCOMPData() {}

    virtual unsigned int		MID()								const = 0;
    virtual double				T()									const = 0;
    virtual double				THETA()								const = 0;
    virtual std::string			SOUT()								const = 0;
};

struct IPCOMPCommand : virtual ICommand {
    virtual ~IPCOMPCommand() {}

    virtual unsigned int		PID()						        const = 0;
    virtual double				Z0()								const = 0;
    virtual double				NSM()								const = 0;
    virtual double				SB()								const = 0;
    virtual std::string			FT()								const = 0;
    virtual double				TREF()								const = 0;
    virtual double				GE()								const = 0;
    virtual std::string			LAM()								const = 0;

    virtual unsigned int		Count()								const = 0;
    virtual const IPCOMPData*	Item(unsigned int index)			const = 0;
};

template<typename O>
struct IEnumerator {
    virtual ~IEnumerator()
    {
    }

    virtual O							Next() = 0;
    virtual void						Skip(int count) = 0;
    virtual void						Reset() = 0;
    virtual void						Destroy() = 0;
    virtual IEnumerator<ICommand*>*		Clone() = 0;
};

struct IFEParserSettings
{
    virtual ~IFEParserSettings() {};

    virtual void        SetFilePath(const char *filePath) = 0;
    virtual const char* GetFilePath() const = 0;
    virtual void        Destroy() = 0;
};

// public interface for the 
template<typename O>
struct ICollection {
    virtual ~ICollection()
    {
    }

    virtual int				Count() = 0;
    virtual O				Item(int zeroBasedIndex) = 0;
    virtual IEnumerator<O>*	GetEnumerator() = 0;
    virtual void			Destroy() = 0;
};

struct ICommandContainer
{
    virtual ~ICommandContainer()
    {
    }

    virtual int Count() = 0;
    virtual Command* Item(int index) = 0;
};

struct ICommandRepository {
public:
    virtual ~ICommandRepository()
    {
    }

    virtual int						Serialize(char** pStream, size_t* pLength)		const = 0;
    virtual int						Deserialize(const char* pStream, size_t length) = 0;
    virtual void					Clear() = 0;
    virtual void					Destroy() = 0;
    virtual void					FreeMemory(void* pMemory) = 0;
    virtual ICollection<ICommand*>*	GetCommandsByName(const char* name) = 0;
    virtual const ICommand*			GetCommandByIndex(int index) = 0;
    virtual int						GetCommandNamesCount(eFECommandsType eCommandsType) = 0;
    virtual const char*				GetCommandName(eFECommandsType eCommandsType, int index) = 0;
    virtual const char*             GetFormat() = 0;
    virtual int                     GetCommandsCount() const = 0;

};

struct IGenericCommand : virtual ICommand {

    virtual int             ArgumentCount()         const = 0;
    virtual const Field*	Argument(int index)     const = 0;
};

// Base public interface for the parser
struct IFEParser
{
    virtual ~IFEParser()
    {
    }

    /*
    Parse the data stream provided as character(byte) array
    inStream        : input stream
    inSize          : length of input stream
    piCommandRepo   : command repository
    */
    virtual int     Parse(const char* inStream, size_t inSize, ICommandRepository* piCommandRepo, const IFEParserSettings *piParserSettings) = 0;

    /*
    Destroy this instance of the parser. The IFEParser instance should not be used after Destroy is called.
    */
    virtual void    Destroy() = 0;
};
