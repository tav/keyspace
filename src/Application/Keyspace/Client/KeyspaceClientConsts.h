#ifndef KEYSPACE_CLIENT_CONSTS_H
#define KEYSPACE_CLIENT_CONSTS_H

#define KEYSPACE_SUCCESS			0
#define KEYSPACE_API_ERROR			-1

#define KEYSPACE_PARTIAL			-101
#define KEYSPACE_FAILURE			-102

#define KEYSPACE_NOMASTER			-201
#define KEYSPACE_NOCONNECTION		-202

#define KEYSPACE_MASTER_TIMEOUT		-301
#define KEYSPACE_GLOBAL_TIMEOUT		-302

#define KEYSPACE_NOSERVICE			-401
#define KEYSPACE_FAILED				-402

#define KEYSPACE_DEFAULT_TIMEOUT	120*1000 // msec

#endif