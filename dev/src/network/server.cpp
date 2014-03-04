#include "server.h"
#include "tcpserver.h"
#include "socket.h"
#include "thread.h"
#include "hostaddress.h"
#include "logger.h"
#include "session.h"
#include "sessionmanager.h"
#include <string>
#include <vector>

namespace Network
{
	class ServerThread : public SDK::Thread
	{
		public:
			ServerThread(const Network::HostAddress& address) : 
			Thread(),
			address_(address)
			{}

			~ServerThread()
			{}

		public:
			void SetAddress(const Network::HostAddress& address)
			{
				address_ = address;
			}

		private:
			virtual bool Run()
			{
				Network::TcpServer s;
				bool res = s.Listen(address_);
				if (!res)
				{
					return false;
				}

				SMPP::SessionManager m;
				bool tmo = false;
				for(;;)
				{
					bool res = s.WaitForNewConnection(10, &tmo);

					if (!res && tmo)
					{
						FILE_LOG(logDEBUG4) << "Timeout !";
						tmo = false;
						continue;
					}

					Network::TcpSocket* client = s.NextPendingConnection();
					if (NULL == client)
					{
						FILE_LOG(logERROR) << "Cannot connect with the SMPP client !";
					}

					SMPP::SmppSession* ps = new SMPP::SmppSession(client);
					client = NULL;

					m.Add(ps);
					ps = NULL;

					/*
						int dataLen = 0;
						unsigned char* buffer = reinterpret_cast<unsigned char*>(&dataLen);
						client->Read(buffer, sizeof(dataLen));

						dataLen = ntohl(dataLen);
						FILE_LOG(logINFO) << "Data len: " << std::hex << std::showbase << dataLen;

						int size = dataLen - 4;
						unsigned char* data = new unsigned char[size];
						client->Read(data, size);

						unsigned char* it = data;

						int tmp = 0;

						memcpy((void*)&tmp, it, sizeof(tmp));
						it += sizeof(tmp);
						FILE_LOG(logINFO) << "Command ID: " << std::setfill('0') << std::setw(2 * sizeof(tmp)) << std::hex << ntohl(tmp);

						memcpy((void*)&tmp, it, sizeof(tmp));
						it += sizeof(tmp);
						FILE_LOG(logINFO) << "Command STATUS: " << std::setfill('0') << std::setw(2 * sizeof(tmp)) << std::hex << ntohl(tmp);

						memcpy((void*)&tmp, it, sizeof(tmp));
						it += sizeof(tmp);
						FILE_LOG(logINFO) << "Sequence Number: " << std::setfill('0') << std::setw(2 * sizeof(tmp)) << std::hex << ntohl(tmp);

						std::string id((const char*)it);
						FILE_LOG(logINFO) << "System ID: " << id; 
						it += id.length() + 1;

						std::string pass((const char*)it);
						FILE_LOG(logINFO) << "Password: " << pass; 
						it += pass.length() + 1;

						std::string type((const char*)it);
						FILE_LOG(logINFO) << "System Type: " << type; 
						it += type.length() + 1;

						unsigned char d = it[0];
						FILE_LOG(logINFO) << "Interface version: " << std::setfill('0') << std::setw(2 * sizeof(int)) << std::hex << (int)d; 

						it += sizeof(d);

						d = it[0];
						FILE_LOG(logINFO) << "Addr_ton: " << std::hex << std::showbase << (int)d; 
						it += sizeof(d);

						d = it[0];
						FILE_LOG(logINFO) << "Addr_npi: " << std::hex << std::showbase << (int)d; 
						it += sizeof(d);

						std::string range((const char*)it);
						FILE_LOG(logINFO) << "Address_range: " << std::hex << std::showbase << range;
						delete[] data;

						//send response
						std::vector<unsigned char> resp;
						int cl = 18;
						cl = htonl(cl);

						const unsigned char* pcl = reinterpret_cast<const unsigned char*>(&cl);

						for (int i = 0; i < sizeof(cl); ++i)
						{
							resp.push_back(pcl[i]);
						}

						cl = 0x80000002;
						cl = htonl(cl);
						for (int i = 0; i < sizeof(cl); ++i)
						{
							resp.push_back(pcl[i]);
						}

						cl = 0x00000000;
						cl = htonl(cl);
						for (int i = 0; i < sizeof(cl); ++i)
						{
							resp.push_back(pcl[i]);
						}

						cl = 0x00000001;
						cl = htonl(cl);
						for (int i = 0; i < sizeof(cl); ++i)
						{
							resp.push_back(pcl[i]);
						}

						std::string smscid("Eugen");
						pcl = reinterpret_cast<const unsigned char*>(smscid.c_str());
						for (int i = 0; i < sizeof(smscid); ++i)
						{
							resp.push_back(pcl[i]);
						}
						resp.push_back(0x00);

						unsigned char* respData = new unsigned char[resp.size()];
						memcpy((void*)respData, &resp[0], resp.size());
						client->Write(respData, resp.size());

						unsigned char* t = respData;
						int i;
						memcpy((void*)&i, t, sizeof(i));
						t += sizeof(i);
						FILE_LOG(logINFO) << "Response: " << std::setfill('0') << std::setw(2 * sizeof(i)) << std::hex << ntohl(i);
						delete[] respData;
					*/
				}

				return true;
			}

		private:
			Network::HostAddress address_;
	};

	Server::Server() : s_(NULL)
	{
	}

	Server::~Server()
	{
		if (NULL != s_)
		{
			s_->Stop();
			delete s_;
		}
	}

	bool Server::Start(const Network::HostAddress& address)
	{
		if (NULL == s_)
		{
			s_ = new ServerThread(address);
		}
		else
		{
			s_->Stop();
			s_->SetAddress(address);
		}

		return s_->Start();
	}

	void Server::Stop()
	{
		if (NULL != s_)
		{
			s_->Stop();
		}
	}

	bool Server::IsRunning() const
	{
		return s_->IsRunning();
	}
}
