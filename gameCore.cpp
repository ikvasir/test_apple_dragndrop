#include "gameCore.h"
#include <QDebug>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

#include "gameDB.h"
#include "gameSound.h"

gameWidget*   gameCore::game = nullptr;
gameMainMenu* gameCore::menu = nullptr;

gameCore::gameCore(QObject* parent) :
	QObject(parent)
{
	gameDB::initDB();
	if (!gameDB::checkDBTables())
	{
		gameDB::initDBTables();
		gameDB::fill_game_table();
		gameDB::fill_resource_table();
	}

	gameSound::init();

	menu = new gameMainMenu();
	menu->show();
}
gameWidget* gameCore::takeGameWidget()
{
	return (game == nullptr)?new gameWidget() : game;
}
gameMainMenu* gameCore::takeMainMenu()
{
	return (menu == nullptr) ? new gameMainMenu() : menu;
}
gameCore* gameCore::instance()
{	
	static gameCore gameCore_;
	return &gameCore_;
}