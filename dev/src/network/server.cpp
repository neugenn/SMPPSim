#include "server.h"
#include "tcpserver.h"
#include "socket.h"
#include "thread.h"
#include "hostaddress.h"
#include "logger.h"
#include "session.h"
#include "BindTransmitter.h"
#include "BindTransmitterResp.h"
#include "EnquireLink.h"
#include "EnquireLinkRes.h"
#include <string>
#include <iomanip>
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
                        continue;
                    }

                    SMPP::Session s(client);
                    client = NULL;
                    FILE_LOG(logINFO) << s;

                    /*
                    unsigned char lenbuf[4];
                    while (client->Read(&lenbuf[0], 4))
                    {
                        SMPP::FourByteInteger dataLen(&lenbuf[0]);

                        FILE_LOG(logINFO) << "Data len: " << dataLen.Value();

                        unsigned char* data = new unsigned char[dataLen.Value()];
                        memcpy(data, &lenbuf[0], 4);
                        ssize_t count = client->Read(data + 4, dataLen.Value() - 4);
                        FILE_LOG(logINFO) << "Read " << count << " bytes !";

                        std::stringstream ss;
                        for (size_t i = 0; i < count + 4; ++i)
                        {
                            ss << std::setfill('0') << std::setw(2) << std::hex << int(data[i]);
                        }
                        FILE_LOG(logINFO) << "Bytes received: " << ss.str();

                        int tmp = 0;
                        memcpy((void*)&tmp, data + 4, sizeof(tmp));
                        FILE_LOG(logINFO) << "Command ID: " << std::setfill('0') << std::setw(2 * sizeof(tmp)) << std::hex << ntohl(tmp);
                        if (0x00000002 == ntohl(tmp))
                        {
                            FILE_LOG(logINFO) << "BindTransmitter message received !";
                            try
                            {
                                SMPP::BindTransmitter t(data);
                                FILE_LOG(logINFO) << t;

                                SMPP::BindTransmitterResp tr;
                                FILE_LOG(logINFO) << tr;
                                tr.SetSequenceNumber(t.GetHeader().GetSequenceNumber());
                                tr.SetSystemId(std::string("EUGEN"));

                                FILE_LOG(logINFO) << tr;

                                const unsigned char* toSend = tr.Data();
                                std::stringstream ss;
                                for (size_t i = 0; i < tr.Size(); ++i)
                                {
                                    ss << std::setfill('0') << std::setw(2) << std::hex << int(toSend[i]);
                                }
                                FILE_LOG(logINFO) << "Bytes to send: " << ss.str();

                                ssize_t count = client->Write(toSend, tr.Size());
                                FILE_LOG(logINFO) << "Sent: " << count;
                            }
                            catch (std::exception& e)
                            {
                                FILE_LOG(logINFO) << "Exception !" << e.what();
                            }
                        }

                        if (0x00000015 == ntohl(tmp))
                        {
                            FILE_LOG(logINFO) << "EnquireLink message received !";
                            SMPP::EnquireLink el(data);
                            FILE_LOG(logINFO) << el;

                            SMPP::EnquireLinkRes elr(data);
                            FILE_LOG(logINFO) << elr;

                            client->Write(elr.Data(), elr.Size());
                        }

                        delete [] data;
                    }
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
