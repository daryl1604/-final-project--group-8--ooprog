/*Daryl De Castro
Maria Fae Escobin
Andrea Lube
Finals OOP*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

// Pet Class
class Pet {
public:
    string name;
    int id;
    int age;
    string healthCondition;
    string gender;
    string type;
    string status;

    Pet(string name, int id, int age, string healthCondition, string gender, string type, string status)
        : name(name), id(id), age(age), healthCondition(healthCondition), gender(gender), type(type), status(status) {}

    void display() {
        cout << id << "\t" << name << "\t" << age << "\t" << healthCondition << "\t" << gender << "\t" << type << "\t" << status << endl;
    }
};

// Singleton Pet Database
class PetDatabase {
public:
    vector<Pet> pets;
    static PetDatabase* instance;

    static PetDatabase* getInstance() {
        if (instance == nullptr) {
            instance = new PetDatabase();
        }
        return instance;
    }

    void addPet(const Pet& pet) {
        pets.push_back(pet);
    }

    void removePet(int id) {
        for (auto it = pets.begin(); it != pets.end(); ++it) {
            if (it->id == id) {
                cout << "Pet ID: " << id << " has been successfully deleted." << endl;
                pets.erase(it);
                return;
            }
        }
        cout << "Pet ID does not exist!" << endl;
    }

    void displayAllPets() {
        if (pets.empty()) {
            cout << "No Pets to Display!" << endl;
        } else {
            cout << "ID\tName\tAge\tHealth\tGender\tType\tStatus" << endl;
            for (auto& pet : pets) {
                pet.display();
            }
        }
    }

    Pet* searchPetByID(int id) {
        for (auto& pet : pets) {
            if (pet.id == id) {
                return &pet;
            }
        }
        return nullptr;
    }

    void sortByAge() {
        sort(pets.begin(), pets.end(), [](const Pet& a, const Pet& b) {
            return a.age < b.age;
        });
        cout << "Pets sorted by age!" << endl;
    }

    void sortByStatus() {
        sort(pets.begin(), pets.end(), [](const Pet& a, const Pet& b) {
            return a.status < b.status;
        });
        cout << "Pets sorted by status!" << endl;
    }
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pet : pets) {
                file << pet.id << "," << pet.name << "," << pet.age << ","
                     << pet.healthCondition << "," << pet.gender << ","
                     << pet.type << "," << pet.status << "\n";
            }
            file.close();
            cout << "Data saved successfully to " << filename << endl;
        } else {
            cout << "Unable to open file for saving." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            pets.clear();
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, health, gender, type, status;
                int id, age;
                char load;

                if (ss >> id >> load &&
                    getline(ss, name, ',') &&
                    ss >> age >> load &&
                    getline(ss, health, ',') &&
                    getline(ss, gender, ',') &&
                    getline(ss, type, ',') &&
                    getline(ss, status)) {
                    pets.emplace_back(name, id, age, health, gender, type, status);
                }
            }
            file.close();
            cout << "Data loaded successfully from " << filename << endl;
        } else {
            cout << "Unable to open file for loading." << endl;
        }
    }

};

PetDatabase* PetDatabase::instance = nullptr;
// User Class 
class User {
public:
    string username;
    string password;
    User(string username, string password) {
        this->username = username;
        this->password = password;
    }
    virtual void Menu() = 0;
    virtual void Option(int option) = 0;
};

class Staff : public User {
public:
	Staff(string username, string password) : User(username, password) {}

    void Menu() override {
    	system("pause");
        system("cls");
        cout << "\nMenu:" << endl;
        cout << "[1] Display Pet Info" << endl;
        cout << "[2] Manage Pet Info" << endl;
        cout << "[3] Delete Pet" << endl;
        cout << "[4] Sort Pets" << endl;
        cout << "[5] Search Pet" << endl;
        cout << "[6] Logout" << endl;
        cout << "[7] Exit" << endl;
    }

    void Option(int option) override {
    	system("cls");
        PetDatabase* petDatabase = PetDatabase::getInstance();
        
        while (cin.fail() || option < 1 || option > 7) { 
	        cin.clear(); 
	        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	        cout << "Invalid option! Please enters number from 1 to 7: ";
	        cin >> option; 
	    }
        switch (option) {
            case 1: {
                petDatabase->displayAllPets();
                break;
            }
            case 2: {
                cout << "\n--- Manage Pet Info ---" << endl;
                int id;
                
                if (petDatabase->pets.empty()) {
                    cout << "No pets available to display!" << endl;
                    break;
                }
                cout << "Enter Pet ID you like to update: ";
                cin >> id;
                while (cin.fail() || id <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input! Pet ID must be a positive number. "<<endl;
                    cout << "Enter Pet ID again: ";
                    cin >> id;
                }
                
                Pet* pet = petDatabase->searchPetByID(id);
                if (pet) {
                    cout << "What would you like to Update?" << endl;
                    cout << "[1] Name" << endl;
                    cout << "[2] Age" << endl;
                    cout << "[3] Health Condition" << endl;
                    cout << "[4] Gender" << endl;
                    cout << "[5] Type" << endl;
                    cout << "[6] Status" << endl;
                    cout << "[7] None" << endl;
                    cout << "Enter your choice: ";
                    
                    int option;
                    cin >> option;
                    system("cls");
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    switch (option) {
                        case 1: {
                            string name;
                            cout << "Enter new Name: ";
                            getline(cin, name);
                            while (name.length() > 100 || !all_of(name.begin(), name.end(), ::isalpha)) {
                                cout << "Invalid input! Name should contain only letters and be less than 100 characters.\nEnter new Name: ";
                                getline(cin, name);
                            }
                            pet->name = name;
                            cout << "Name updated successfully!" << endl;
                            break;
                        }
                        case 2: {
                            int age;
                            cout << "Enter new Age: ";
                            cin >> age;
                            while (cin.fail() || age <= 0 || age > 99) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid input! Age must be a positive number between 1 and 99.\nEnter new Age: ";
                                cin >> age;
                            }
                            pet->age = age;
                            cout << "Age updated successfully!" << endl;
                            break;
                        }
                        case 3: {
                            string health;
                            cout << "Enter new Health Condition (Healthy, Ill, Injured): ";
                            getline(cin, health);
                            transform(health.begin(), health.end(), health.begin(), ::tolower);
                            while (health != "healthy" && health != "ill" && health != "injured") {
                                cout << "Invalid input! Please enter one of the following: Healthy, Ill, Injured.\nEnter new Health Condition: ";
                                getline(cin, health);
                                transform(health.begin(), health.end(), health.begin(), ::tolower);
                            }
                            pet->healthCondition = health;
                            cout << "Health Condition updated successfully!" << endl;
                            break;
                        }
                        case 4: {
                            string gender;
                            cout << "Enter new Gender (Male/Female): ";
                            getline(cin, gender);
                            transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
                            while (gender != "male" && gender != "female") {
                                cout << "Invalid input! Please enter 'male' or 'female'.\nEnter new Gender: ";
                                getline(cin, gender);
                                transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
                            }
                            pet->gender = gender;
                            cout << "Gender updated successfully!" << endl;
                            break;
                        }
                        case 5: {
                            string type;
                            cout << "Enter new Type (Dog, Cat, Rabbit, Bird, Hamster, Turtle, Fish): ";
                            getline(cin, type);
                            transform(type.begin(), type.end(), type.begin(), ::tolower);
                            while (type != "dog" && type != "cat" && type != "rabbit" && type != "bird" &&
                                   type != "hamster" && type != "turtle" && type != "fish") {
                                cout << "Invalid input! Please enter one of the following: Dog, Cat, Rabbit, Bird, Hamster, Turtle, Fish.\nEnter new Type: ";
                                getline(cin, type);
                                transform(type.begin(), type.end(), type.begin(), ::tolower);
                            }
                            pet->type = type;
                            cout << "Type updated successfully!" << endl;
                            break;
                        }
                        case 6: {
                            string status;
                            cout << "Enter new Status (available/adopted): ";
                            getline(cin, status);
                            transform(status.begin(), status.end(), status.begin(), ::tolower);
                            while (status != "available" && status != "adopted") {
                                cout << "Invalid input! Please enter 'available' or 'adopted'.\nEnter new Status: ";
                                getline(cin, status);
                                transform(status.begin(), status.end(), status.begin(), ::tolower);
                            }
                            pet->status = status;
                            cout << "Status updated successfully!" << endl;
                            break;
                        }
                        case 7:
                            cout << "No updates made." << endl;
                            break;
                        default:
                            cout << "Invalid option!" << endl;
                            break;
                    }
                } else {
                    cout << "Pet ID does not exist!" << endl;
                }
                break;
            }
            case 3: {
                int id;
                
                if (petDatabase->pets.empty()) {
                    cout << "No pets available to display!" << endl;
                    break;
                }
                cout << "Enter Pet ID to delete: ";
                cin >> id;
                while (cin.fail() || id <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input! Pet ID must be a positive number. "<<endl;
                    cout << "Enter Pet ID again: ";
                    cin >> id;
                }
                petDatabase->removePet(id);
                break;
            }
            case 4: {
                int choice;
                bool condition = false;
                
                if (petDatabase->pets.empty()) {
                    cout << "No pets available to display!" << endl;
                    break;
                }
                while (!condition) {
                    cout << "\nSort Pets by:\n";
                    cout << "1. Age (Ascending)\n";
                    cout << "2. Availability (Adopted First)\n";
                    cout << "3. Back\n";
                    cout << "Enter your choice (1, 2, or 3): ";
                    
                    if (!(cin >> choice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number (1, 2, or 3).\n";
                        continue;
                    }
                
                    if (choice == 1) {
                        petDatabase->sortByAge();
                        petDatabase->displayAllPets();
                        condition = true;
                    }
                    else if (choice == 2) {
                        petDatabase->sortByStatus();
                        petDatabase->displayAllPets();
                        condition = true;
                    }
                    else if (choice == 3) {
                        cout << "Returning to Menu...";
                        condition = true;
                    }
                    else {
                        cout << "Invalid choice! Please enter 1, 2, or 3.\n";
                    }
                }
                break;
            }
            case 5: {
                PetDatabase* petDatabase = PetDatabase::getInstance();
            
                if (petDatabase->pets.empty()) {
                    cout << "No pets available to display!" << endl;
                    break;
                }
            
                int id;
                cout << "Enter Pet ID: ";
                while (!(cin >> id) || id <= 0) {
                    cout << "Invalid input! Please enter a valid positive number for Pet ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            
                Pet* pet = petDatabase->searchPetByID(id);
                if (pet) {
                    cout << "\n--- Pet Details ---" << endl;
                    cout << "Pet Name: " << pet->name << endl;
                    cout << "Age: " << pet->age << endl;
                    cout << "Gender: " << pet->gender << endl;
                    cout << "Type: " << pet->type << endl;
                    cout << "Health Condition: " << pet->healthCondition << endl;
                    cout << "Status: " << pet->status << endl;
                } else {
                    cout << "Pet not found!" << endl;
                }
                break;
            }
            case 6: {
                cout << "Logging out..." << endl;
                return;
            }
            case 7: {
                exit(0);
                break;
            }
            default:
                cout << "Invalid option! Please try again." << endl;
                break;
        }
    }
};



class Adoptor : public User {
public:
    Adoptor(string username, string password) : User(username, password) {}

    void Menu() override {
        bool condition = false;
        while (!condition) {
            int option;
            system("pause");
	        system("cls");
            cout << "\nMenu:" << endl;
            cout << "[1] Display Pet Info" << endl;
            cout << "[2] Sort Pets" << endl;
            cout << "[3] Search Pet" << endl;
            cout << "[4] Adopt a Pet" << endl;
            cout << "[5] Logout" << endl;
            cout << "[6] Exit" << endl;
            cout << "Select an option: ";
            cin >> option;
            system("cls");
            
            while (cin.fail() || option < 1 || option > 6) {// para d magaksep number or letter maliban sa 1 to 6
		        cin.clear();  
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
		        cout << "Invalid option! Please enter a number between 1 and 6: ";
		        cin >> option;  
		    }

            if (option == 5) {
                cout << "Logged out successfully!" << endl;
                break; // babalik sa user role selectionn
            } else if (option == 6) {
                cout << "\nExiting Program..." << endl;
                exit(0); // Exit 
            } else {
                Option(option);
            }
        }
    }

    void Option(int option) override {
    	PetDatabase* petDatabase = PetDatabase::getInstance();
        
        switch (option) {
            case 1: {
                petDatabase->displayAllPets();
                break;
            }
            case 2: {
                int choice;
                bool sortCondition = false;

                if (petDatabase->pets.empty()) {
                    cout << "No pets available to display!" << endl;
                    break;
                }

                while (!sortCondition) {
                    cout << "\nSort Pets by:\n";
                    cout << "1. Age (Ascending)\n";
                    cout << "2. Availability (Adopted First)\n";
                    cout << "3. Back\n";
                    cout << "Enter your choice (1, 2, or 3): ";

                    if (!(cin >> choice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number (1, 2, or 3).\n";
                        continue;
                    }

                    if (choice == 1) {
                        petDatabase->sortByAge();
                        petDatabase->displayAllPets();
                        sortCondition = true;
                    } else if (choice == 2) {
                        petDatabase->sortByStatus();
                        petDatabase->displayAllPets();
                        sortCondition = true;
                    } else if (choice == 3) {
                        cout << "Returning to Menu...\n";
                        sortCondition = true;
                    } else {
                        cout << "Invalid choice! Please enter 1, 2, or 3.\n";
                    }
                }
                break;
            }
            case 3: {
                int id;
                cout << "Enter Pet ID: ";
                while (!(cin >> id) || id <= 0) {
                    cout << "Invalid input! Please enter a valid positive number for Pet ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                Pet* pet = petDatabase->searchPetByID(id);
                if (pet) {
                    cout << "\n--- Pet Details ---" << endl;
                    cout << "Pet Name: " << pet->name << endl;
                    cout << "Age: " << pet->age << endl;
                    cout << "Gender: " << pet->gender << endl;
                    cout << "Type: " << pet->type << endl;
                    cout << "Health Condition: " << pet->healthCondition << endl;
                    cout << "Status: " << pet->status << endl;
                } else {
                    cout << "Pet not found!" << endl;
                }
                break;
            }
            case 4: {
                int id;

                if (petDatabase->pets.empty()) {
                    cout << "No pets available to display!" << endl;
                    break;
                }

                cout << "Enter Pet ID to adopt: ";
                while (!(cin >> id) || id <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a valid positive number for Pet ID: ";
                }

                Pet* pet = petDatabase->searchPetByID(id);
                if (pet) {
                    if (pet->status == "available") {
                        pet->status = "adopted";
                        cout << "You have successfully adopted " << pet->name << "!" << endl;
                    } else {
                        cout << "Sorry, this pet has already been adopted." << endl;
                    }
                } else {
                    cout << "Pet not found!" << endl;
                }
                break;
            }
            default:
                cout << "Invalid option! Please try again." << endl;
                break;
        }
    }
};




class Admin : public User {
public:
	vector<User*> userAccounts;
     Admin(string username, string password) : User(username, password) {}
     
    void Menu() override {
    	system("pause");
        system("cls");
        cout << "\nMenu:" << endl;
        cout << "[1] Add Account" << endl;
        cout << "[2] Add Pet" << endl;
        cout << "[3] Display Pet Info" << endl;
        cout << "[4] Manage Pet Info" << endl;
        cout << "[5] Delete Pet" << endl;
        cout << "[6] Sort Pets" << endl;
        cout << "[7] Search Pet" << endl;
        cout << "[8] Logout" << endl;
        cout << "[9] Exit" << endl;
        cout << "[10] Save Pets to File" << endl;
		cout << "[11] Load Pets from File" << endl;

    }

    void Option(int option) override {
    	
    while (cin.fail() || option < 1 || option > 11) {// para d magaksep number or letter maliban sa 1 to 11
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cout << "Invalid option! Please enter a number between 1 and 11: ";
        cin >> option;  
    }
    	system("cls");
        PetDatabase* petDatabase = PetDatabase::getInstance();
        switch (option) {
	        case 1: { // Add Account
			    int choice;
			    cout << "Add Account For:" << endl;
			    cout << "[1] Admin" << endl;
			    cout << "[2] Staff" << endl;
			    cout << "[3] Adopter" << endl;
			    cout << "Enter your choice: ";
			    cin >> choice;
			
			    string newUsername, newPassword;
			    cout << "Enter Username: ";
			    cin >> newUsername;
			    cout << "Enter Password: ";
			    cin >> newPassword;
			
			    User* newUser = nullptr; // para ma initialize yung newuser pointer
			    if (choice == 1) {
			        newUser = new Admin(newUsername, newPassword);
			    } else if (choice == 2) {
			        newUser = new Staff(newUsername, newPassword);
			    } else if (choice == 3) {
			        newUser = new Adoptor(newUsername, newPassword);
			    } else {
			        cout << "Invalid choice!" << endl;
			        return;
			    }
			
			    
			    extern vector<User*> userAccounts; 
			    userAccounts.push_back(newUser);
			
			    cout << "Account added successfully!" << endl;
			    break;
			}
            case 2: {
            	cout<<"A D D  P E T"<<endl;
                // Add Pet
                string name, health, gender, type, status;
                int id, age;
                
				cout << "Enter Pet Name: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, name);
				
				while (name.length() > 100 || !all_of(name.begin(), name.end(), ::isalpha)) {//validation para d mag aksep numbers at limited sa 100 charas
				    cout << "Invalid input! Pet Name should contain only letters and be less than 100 characters." << endl;
				    cout << "Enter Pet Name: ";
				    getline(cin, name);
				}
				
				cout << "Enter Pet ID: ";
				cin >> id;
				while (cin.fail() || id <= 0) {//validation para d mag aksep ng chareas and negative numbers
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    cout << "\nInvalid input! Pet ID must be a positive number. "<<endl;
				    cout << "Enter Pet ID again: ";
				    cin >> id;
				}
				
				while (petDatabase->searchPetByID(id)) {// validation para d mag aksep pag same id
				    cout << "\nID already exists! Please use another ID "<<endl;
				    cout << "\nEnter Pet ID: ";
				    cin >> id;
				}
				
				cout << "Enter Pet Age: ";
				cin >> age;
				while (cin.fail() || age <= 0 || age > 99) {// para di mag aksep letters at 0-99 lang
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    cout << "\nInvalid input! Pet Age must be a positive number between 1 and 99. Please enter Age again: ";
				    cin >> age;
				} 
				
				cout << "Enter Health Condition (Healthy, Ill, Injured): ";//health condition 
				cin.ignore();
				getline(cin, health);
				transform(health.begin(), health.end(), health.begin(), ::tolower);
				
				while (health != "healthy" && health != "ill" && health != "injured") {// validation para mag aksep lang nung 3 words na naka indicate
				    cout << "\nInvalid input! Please enter one of the following: Healthy, Ill, Injured: ";
				    getline(cin, health);
				    transform(health.begin(), health.end(), health.begin(), ::tolower);
				}
				
				cout << "Enter Gender (Male/Female): ";
				getline(cin, gender);
				transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
				
				while (gender != "male" && gender != "female") {
				    cout << "\nInvalid input! Please enter 'male' or 'female': ";// validation para magaksep lng ng male at female
				    getline(cin, gender);
				    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
				}
				
				cout << "Enter Type(Dog, Cat, Rabbit, Bird, Hamster, Turtle, Fish): ";
				getline(cin, type);
				transform(type.begin(), type.end(), type.begin(), ::tolower);
				
				while (type != "dog" && type != "cat" && type != "rabbit" && type != "bird" && type != "hamster" && type != "turtle" && type != "fish") {// validation para d magaksep ng other words o numbers maliban sa naka indicate
				    cout << "\nInvalid input! Please enter one of the following: Dog, Cat, Rabbit, Bird, Hamster, Turtle, Fish: ";
				    getline(cin, type);
				    transform(type.begin(), type.end(), type.begin(), ::tolower);
				}
				
				cout << "Enter Status (available/adopted): ";
				getline(cin, status);
				transform(status.begin(), status.end(), status.begin(), ::tolower);
				
				while (status != "available" && status != "adopted") {
				    cout << "Invalid input! Please enter 'available' or 'adopted': ";//validation para aksepin lang dalawang words na naka indicate
				    getline(cin, status);
				    transform(status.begin(), status.end(), status.begin(), ::tolower);
				}
				cout << "\nPet Added Succesfully!!!";
				
				petDatabase->addPet(Pet(name, id, age, health, gender, type, status));

                break;
            }
            case 3: {
                petDatabase->displayAllPets();
                break;
            }
			case 4: {
			    cout << "\n--- Manage Pet Info ---" << endl;
			    int id;
			    
			    if (petDatabase->pets.empty()) {
			        cout << "No pets available to display!" << endl;//pag wala pa nadadagdag na pets eto lalabas
			        break;
			    }
			    cout << "Enter Pet ID you like to update: ";
			    cin >> id;
			    while (cin.fail() || id <= 0) {//validation kapag ang ininput ay negative number or chara d mag aaksep
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    cout << "\nInvalid input! Pet ID must be a positive number. "<<endl;
				    cout << "Enter Pet ID again: ";
				    cin >> id;
				}
			
			    Pet* pet = petDatabase->searchPetByID(id);
			    if (pet) {
			        cout << "What would you like to Update?" << endl;
			        cout << "[1] Name" << endl;
			        cout << "[2] Age" << endl;
			        cout << "[3] Health Condition" << endl;
			        cout << "[4] Gender" << endl;
			        cout << "[5] Type" << endl;
			        cout << "[6] Status" << endl;
			        cout << "[7] None" << endl;
			        cout << "Enter your choice: ";
			
			        int option;
			        cin >> option;
			        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			
			        switch (option) {
			            case 1: {
			                string name;
			                cout << "Enter new Name: ";
			                getline(cin, name);
			                while (name.length() > 100 || !all_of(name.begin(), name.end(), ::isalpha)) {
			                    cout << "Invalid input! Name should contain only letters and be less than 100 characters.\nEnter new Name: ";
			                    getline(cin, name);
			                }
			                pet->name = name;
			                cout << "Name updated successfully!" << endl;
			                break;
			            }
			            case 2: {
			                int age;
			                cout << "Enter new Age: ";
			                cin >> age;
			                while (cin.fail() || age <= 0 || age > 99) {
			                    cin.clear();
			                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
			                    cout << "Invalid input! Age must be a positive number between 1 and 99.\nEnter new Age: ";
			                    cin >> age;
			                }
			                pet->age = age;
			                cout << "Age updated successfully!" << endl;
			                break;
			            }
			            case 3: {
			                string health;
			                cout << "Enter new Health Condition (Healthy, Ill, Injured): ";
			                getline(cin, health);
			                transform(health.begin(), health.end(), health.begin(), ::tolower);
			                while (health != "healthy" && health != "ill" && health != "injured") {
			                    cout << "Invalid input! Please enter one of the following: Healthy, Ill, Injured.\nEnter new Health Condition: ";
			                    getline(cin, health);
			                    transform(health.begin(), health.end(), health.begin(), ::tolower);
			                }
			                pet->healthCondition = health;
			                cout << "Health Condition updated successfully!" << endl;
			                break;
			            }
			            case 4: {
			                string gender;
			                cout << "Enter new Gender (Male/Female): ";
			                getline(cin, gender);
			                transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
			                while (gender != "male" && gender != "female") {
			                    cout << "Invalid input! Please enter 'male' or 'female'.\nEnter new Gender: ";
			                    getline(cin, gender);
			                    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
			                }
			                pet->gender = gender;
			                cout << "Gender updated successfully!" << endl;
			                break;
			            }
			            case 5: {
			                string type;
			                cout << "Enter new Type (Dog, Cat, Rabbit, Bird, Hamster, Turtle, Fish): ";
			                getline(cin, type);
			                transform(type.begin(), type.end(), type.begin(), ::tolower);
			                while (type != "dog" && type != "cat" && type != "rabbit" && type != "bird" &&
			                       type != "hamster" && type != "turtle" && type != "fish") {
			                    cout << "Invalid input! Please enter one of the following: Dog, Cat, Rabbit, Bird, Hamster, Turtle, Fish.\nEnter new Type: ";
			                    getline(cin, type);
			                    transform(type.begin(), type.end(), type.begin(), ::tolower);
			                }
			                pet->type = type;
			                cout << "Type updated successfully!" << endl;
			                break;
			            }
			            case 6: {
			                string status;
			                cout << "Enter new Status (available/adopted): ";
			                getline(cin, status);
			                transform(status.begin(), status.end(), status.begin(), ::tolower);
			                while (status != "available" && status != "adopted") {
			                    cout << "Invalid input! Please enter 'available' or 'adopted'.\nEnter new Status: ";
			                    getline(cin, status);
			                    transform(status.begin(), status.end(), status.begin(), ::tolower);
			                }
			                pet->status = status;
			                cout << "Status updated successfully!" << endl;
			                break;
			            }
			            case 7:
			                cout << "No updates made." << endl;
			                break;
			            default:
			                cout << "Invalid option!" << endl;
			                break;
			        }
			    } else {
			        cout << "Pet ID does not exist!" << endl;
			    }
			    break;
			}

            case 5: {
                int id;
                
                if (petDatabase->pets.empty()) {
			        cout << "No pets available to display!" << endl;
			        break;
			    }
                cout << "Enter Pet ID to delete: ";
                cin >> id;
                while (cin.fail() || id <= 0) {
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(), '\n');
				    cout << "\nInvalid input! Pet ID must be a positive number. "<<endl;
				    cout << "Enter Pet ID again: ";
				    cin >> id;
				}
                petDatabase->removePet(id);
                break;
            }
            
			case 6: {
			    int choice;
			    bool condition = false;
			    
			    if (petDatabase->pets.empty()) {
			        cout << "No pets available to display!" << endl;
			        break;
			    }
			    while (!condition) {
			        cout << "\nSort Pets by:\n";
			        cout << "1. Age (Ascending)\n";
			        cout << "2. Availability (Adopted First)\n";
			        cout << "3. Back\n";
			        cout << "Enter your choice (1, 2, or 3): ";
			        
			        if (!(cin >> choice)) {
			            cin.clear();
			            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			            cout << "Invalid input! Please enter a number (1, 2, or 3).\n";
			            continue;
			        }
			
			        if (choice == 1) {
			            petDatabase->sortByAge();
			            petDatabase->displayAllPets();
			            condition = true;
			        }
			        else if (choice == 2) {
			            petDatabase->sortByStatus();
			            petDatabase->displayAllPets();
			            condition = true;
			        }
			        else if (choice == 3) {
			            cout << "Returning to Menu...";
			            condition = true;
			        }
			        else {
			            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
			        }
			    }
			    break;
			}
			

			case 7: {
			    PetDatabase* petDatabase = PetDatabase::getInstance();
			
			    if (petDatabase->pets.empty()) {
			        cout << "No pets available to display!" << endl;
			        break;
			    }
			
			    int id;
			    cout << "Enter Pet ID: ";
			    while (!(cin >> id) || id <= 0) {
			        cout << "Invalid input! Please enter a valid positive number for Pet ID: ";
			        cin.clear();
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    }
			
			    Pet* pet = petDatabase->searchPetByID(id);
			    if (pet) {
			        cout << "\n--- Pet Details ---" << endl;
			        cout << "Pet Name: " << pet->name << endl;
			        cout << "Age: " << pet->age << endl;
			        cout << "Gender: " << pet->gender << endl;
			        cout << "Type: " << pet->type << endl;
			        cout << "Health Condition: " << pet->healthCondition << endl;
			        cout << "Status: " << pet->status << endl;
			    } else {
			        cout << "Pet ID does not exist!" << endl;
			    }
			    break;
			}

            case 8:
                cout << "Logged out successfully!" << endl;
                return;
            case 9:
                exit(0);
            case 10:
			    petDatabase->saveToFile("pets.txt");
			    break;
			case 11:
			    petDatabase->loadFromFile("pets.txt");
			    break;

            default:
                cout << "Invalid option!" << endl;
        }
    }
};

vector<User*> userAccounts;


int main() {
    Admin* predefinedAdmin = new Admin("admin", "password");
    Staff* predefinedStaff = new Staff("staff1", "password");
    Adoptor* predefinedAdopter = new Adoptor("adoptor1", "password");

    userAccounts.push_back(predefinedAdmin);
    userAccounts.push_back(predefinedStaff);
    userAccounts.push_back(predefinedAdopter);

    bool condition = false;
    User* user = nullptr;

    while (!condition) {
        int choice;
        system("cls");
        cout << "\nSelect User Role:" << endl;
        cout << "[1] Admin" << endl;
        cout << "[2] Staff" << endl;
        cout << "[3] Adopter" << endl;
        cout << "[4] Exit" << endl;
        cout << "Enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid input! Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: { // Admin login
                string username, password;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;

                bool loggedIn = false;
                for (auto& account : userAccounts) {
                    if (account->username == username && account->password == password) {
                        loggedIn = true;
                        user = account;
                        break;
                    }
                }

                if (loggedIn) {
                    cout << "Logged in successfully!" << endl;
                    bool logout = false;
                    while (!logout) {
                        user->Menu();
                        int option;
                        cout << "Enter your choice: ";
                        cin >> option;
                        user->Option(option);
                        if (option == 8) { 
                            logout = true;
                        }
                    }
                } else {
                    cout << "Invalid Username or Password!" << endl;
                }
                break;
            }
            case 2: { // Staff login
                string username, password;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;

                bool loggedIn = false;
                for (auto& account : userAccounts) {
                    if (account->username == username && account->password == password) {
                        loggedIn = true;
                        user = account;
                        break;
                    }
                }

                if (loggedIn) {
                    cout << "Logged in successfully!" << endl;
                    bool logout = false;
                    while (!logout) {
                        user->Menu();
                        int option;
                        cout << "Enter your choice: ";
                        cin >> option;
                        user->Option(option);
                        if (option == 6) { 
                            logout = true;
                        }
                    }
                } else {
                    cout << "Invalid Username or Password!" << endl;
                }
                break;
            }
            case 3: { // Adopter login
                string username, password;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;

                bool loggedIn = false;
                for (auto& account : userAccounts) {
                    if (account->username == username && account->password == password) {
                        loggedIn = true;
                        user = account;
                        break;
                    }
                }

                if (loggedIn) {
                    cout << "Logged in successfully!" << endl;
                    user->Menu();
                } else {
                    cout << "Invalid Username or Password!" << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting Program!" << endl;
                condition = true;
                break;
            default:
            	system("pause");
                cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
