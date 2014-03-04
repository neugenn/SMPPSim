#ifndef SESSION_MANAGER_H_
#define SESSION_MANAGER_H_

#include <vector>
#include <cassert>

namespace SMPP
{
	class SmppSession;

	class SessionManager
	{
		public:
			SessionManager() : sessions_() 
			{}

			~SessionManager() 
			{}

		public:
			void Add(SmppSession*& s)
			{
				assert(NULL != s);

				sessions_.push_back(s);
				s = NULL;
			}

		private:
			std::vector<SmppSession*> sessions_;
	};
}

#endif // SESSION_MANAGER_H_

