#include <QString>

struct VM
{
	QString name;
	QString UID;

	VM(QString name, QString UID)
	{
		this->name = name;
		this->UID = UID;
	}
};
