#include <UnitTest++/UnitTest++.h>
#include "ServerClientInterface.h"


using namespace std;

struct User_fix {
	User * p;
	User_fix() {
		p = new User();
	}
	~User_fix() {
		delete p;
	}
};

    // Модуль User.h

	// Ошибка идентификации
	TEST_FIXTURE(User_fix, SuccessfulIdentificatio){
		p->set_ID("user");
		auto resultat = p->СheckLogin({"user", "ivanov", "user0"});
		// Проверяем результат
		UNITTEST_CHECK_EQUAL(resultat, 1);
	}


	// Ошибка идентификации
	TEST_FIXTURE(User_fix, IdentificationError){
		p->set_ID("user");
		auto resultat = p->СheckLogin({"ivanov", "user0"});
		// Проверяем результат
		UNITTEST_CHECK_EQUAL(resultat, 0);
	}
	// Удачная аутентификация
	TEST_FIXTURE(User_fix, SuccessfulAuthentication){
		p->set_ID("user");
		p->set_hash("B77654515B81DCF72FCF0387A1EF6C54");
		auto resultat = p->CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "1AF4D801F8BBA41A");
		// Проверяем результат
		UNITTEST_CHECK_EQUAL(resultat, 1);

	}

	// Ошибка аутентификации
	TEST_FIXTURE(User_fix, AuthenticationError){
		p->set_ID("user");
		p->set_hash("B77654515B81DCF72FCF0387A1EF6C51");
		auto resultat = p->CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "1AF4D801F8BBA41A");
		// Проверяем результат
		UNITTEST_CHECK_EQUAL(resultat, 0);
	}

	struct Errors_fix {
	Errors * l;
	Errors_fix() {
		l = new Errors();
	}
	~Errors_fix() {
		delete l;
	}
};

    // Ошибка открытия журнала
    TEST_FIXTURE(Errors_fix, LogOpeningError){
        CHECK_THROW(l->set_File_Log("!/#@/log.conf"), invalid_argument);
    }

	struct DataReader_fix {
	DataReader * r;
	DataReader_fix() {
		r = new DataReader();
	}
	~DataReader_fix() {
		delete r;
	}
};

    // Ошибка открытия БД
    TEST_FIXTURE(DataReader_fix, DatabaseOpeningError){
        r-> set_FileReader("!@//DB_client.conf");
        CHECK_THROW(r->getClient(), invalid_argument);
        
    }

    // Ошибка открытия БД
    TEST_FIXTURE(DataReader_fix, EmptyDatabaseFile){
        r-> set_FileReader("None.conf");
        CHECK_THROW(r->getClient(), invalid_argument);
    }

    // Получение БД из файла
    TEST_FIXTURE(DataReader_fix, FetchingDatabaseFromFile){
        r-> set_FileReader("DB.conf");
        auto resultat = r->getClient();

        vector<std::string> login_test = resultat.first;
        vector<std::string> password_test = resultat.second;

		vector<std::string> login = {"user", "ivanov", "user0"};
		vector<std::string> password = {"P@ssW0rd", "123456", "qwe123"};
		cout << endl;

        if(login_test != login){
            CHECK(false);
        }

        if(password_test != password){
            CHECK(false);
        }

        CHECK(true);
    }

struct Server_fix {
	ServerClientInterface * s;
	Server_fix() {
		s = new ServerClientInterface();
	}
	~Server_fix() {
		delete s;
	}
};

    // Ошибка в адресе сервера
    TEST_FIXTURE(Server_fix, ServerAddressError){
        CHECK_THROW(s->set_address("101.101.101.101"), invalid_argument);
    }
    // Ошибка в порту сервера
    TEST_FIXTURE(Server_fix, ServerPortError){
        CHECK_THROW(s->set_address("104"), invalid_argument);
    }
    // суммирование элементов векторов
    TEST_FIXTURE(Server_fix, VectorElementsSum){
		s->set_vec({5, 6, 7, 8});
        auto resultat = s->sum_vec();
        UNITTEST_CHECK_EQUAL(resultat, 26);
    }

    // Переполнение вверх при суммировании элементов векторов
    TEST_FIXTURE(Server_fix, OverflowUpwardInVectorElementsSum){
        s->set_vec({9223372036854775807, 1});
        auto resultat = s->sum_vec();
        UNITTEST_CHECK_EQUAL(resultat, 9223372036854775807);
    }


int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}