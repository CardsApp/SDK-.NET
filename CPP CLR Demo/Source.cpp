#using <mscorlib.dll>

using namespace System;
using namespace Cards;

void HandleCardTap(CardTapResponse ^ cardInfo);
void HandleStatusChange(ReaderStatus readerStatus);

int main(array<System::String ^> ^args)
{
	//Create reader settings
	ReaderSettings ^ readerSettings = gcnew ReaderSettings("ACS - ACR122U PICC Interface");

	//Create reader credentials
	ReaderCredentials ^ readerCredentials = gcnew ReaderCredentials("ABCDE1234ABCDE1234ABCDE1234");

	//Create a card reader
	CardReader ^ cardReader = gcnew CardReader(readerSettings, readerCredentials);

	//Subscribe to Card Tap event
	cardReader->OnCardTap += gcnew Cards::CardTapHandler(HandleCardTap);

	//Subscribe to Status Change event
	cardReader->OnStatusChange += gcnew Cards::StatusChangeHandler(HandleStatusChange);

	//Start listening!
	cardReader->Listen();

	return 0;
}

/// <summary>
/// Handle Card Tap event. This event is raised when a user taps his phone on the reader. 
/// Note that Cards must be installed on the phone.
/// </summary>
void HandleCardTap(CardTapResponse ^ cardInfo)
{
	if (!cardInfo->IsSuccess)
	{
		throw gcnew Exception(String::Format("Failed reading card, error: [{0}] {1}", (int)cardInfo->Error, cardInfo->Error.ToString()));
	}

	Console::WriteLine(String::Format("Card read, user ID: '{0}'.", cardInfo->CardDetails->UserID));

	//Your code goes here!
	//Do whatever you want with the accepted User ID!

	//-----------------------
	//Example: Open the door, if the user is authorized
	//-----------------------
	/*if (YourSystem.IsAuthorizedToOpenDoor(cardInfo.CardDetails.UserID, Doors.Hallway))
	{
	YourSystem.OpenDoor(Doors.Hallway);
	}
	*/

	//-----------------------
	//Example: Remove balance
	//-----------------------
	/*
	YourSystem.Users.ChangeBalance(cardInfo.CardDetails.UserID, -10);
	*/
}

/// <summary>
/// Handles reader status change. 
/// </summary>
void HandleStatusChange(ReaderStatus readerStatus)
{
	switch (readerStatus)
	{
	case ReaderStatus::Disconnected:
		Console::WriteLine("Card reader has been disconnected!");
		break;
	case ReaderStatus::Connected:
		Console::WriteLine("Card reader has been connected!");
		break;
	}
}