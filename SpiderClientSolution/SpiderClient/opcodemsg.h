#pragma once

#define	NOTHING (0)
#define	WAY (1)
#define IAM (2)
#define QALIVE (3)
#define AALIVE (4)
#define QUIT (5)
#define SLEEP (6)
#define WAKEUP (7)
#define REMOVE (8)
#define SENDKEYLOG (9)
#define TAKEDATNAME (10)
#define CMDNOTFOUND (11)
#define SENDMOUSELOG (12)
#define OP_FAIL (13)

#define	WAIT_OPC (32)
#define	OPC_DONE (33)
#define	SEND (34)
#define	READ (35)

typedef struct s_msg
{
	int	code;
	int	nbmsg;
	int	timestamps;
	int	size;
	std::string *data;
}			t_msg;