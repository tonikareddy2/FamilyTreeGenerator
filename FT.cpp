#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Individual {
private:
    string name;
    string birthdate;
    vector<Individual*> children;

public:
    Individual(string n, string b) : name(n), birthdate(b) {}

    void addChild(Individual* child) {
        children.push_back(child);
    }

    string getName() const {
        return name;
    }

    string getBirthdate() const {
        return birthdate;
    }

    vector<Individual*>& getChildren() {
        return children;
    }

    const vector<Individual*>& getChildren() const {
        return children;
    }
};

class FamilyTree {
private:
    Individual* root;

public:
    FamilyTree(string rootName, string rootBirthdate) {
        root = new Individual(rootName, rootBirthdate);
    }

    void addChild(Individual* parent, Individual* child) {
        parent->addChild(child);
    }

    Individual* searchIndividual(Individual* node, const string& name) {
        if (node == nullptr) return nullptr;

        if (node->getName() == name) return node;

        for (Individual* child : node->getChildren()) {
            Individual* found = searchIndividual(child, name);
            if (found) return found;
        }
        return nullptr;
    }

    void visualizeTree(const Individual* node, int depth) {
        if (node == nullptr) return;

        for (int i = 0; i < depth; i++) {
            cout << "  ";  // Indentation for a visual hierarchy
        }
        cout << node->getName() << " (" << node->getBirthdate() << ")" << endl;

        for (const Individual* child : node->getChildren()) {
            visualizeTree(child, depth + 1);
        }
    }

    Individual* getRoot() const {
        return root;
    }

    void destroyPerson(Individual* node, const string& name) {
        if (!node) return;

        if (node->getName() == name) {
            for (Individual* child : node->getChildren()) {
                destroyPerson(child, child->getName());
            }
            delete node;
            root = nullptr;
            return;
        }

        auto& children = node->getChildren();
        for (size_t i = 0; i < children.size(); ++i) {
            if (children[i]->getName() == name) {
                destroyPerson(children[i], name);
                children.erase(children.begin() + i);
                return;
            }
        }
    }

    void findRelationship(Individual* node1, Individual* node2) {
        if (!node1 || !node2) {
            cout << "One or both persons not found in the family tree." << endl;
            return;
        }

        for (Individual* child : node1->getChildren()) {
            if (child == node2) {
                cout << node1->getName() << " is the parent of " << node2->getName() << endl;
                return;
            }
        }
        for (Individual* child : node2->getChildren()) {
            if (child == node1) {
                cout << node2->getName() << " is the parent of " << node1->getName() << endl;
                return;
            }
        }
        cout << node1->getName() << " and " << node2->getName() << " are related, but further logic can be implemented here." << endl;
    }
};

FamilyTree changeFamilyTree() {
    string newRootName, newRootBirthdate;
    cout << "Enter new root person's name: ";
    cin.ignore();
    getline(cin, newRootName);
    cout << "Enter new root person's birthdate: ";
    getline(cin, newRootBirthdate);
    
    FamilyTree newFamily(newRootName, newRootBirthdate);
    cout << "Family tree root changed successfully." << endl;
    return newFamily;
}

FamilyTree connectTwoFamilyTrees(FamilyTree& family1, FamilyTree& family2) {
    string newRootName, newRootBirthdate;
    cout << "Enter the name of the new common ancestor: ";
    cin.ignore();
    getline(cin, newRootName);
    cout << "Enter the birthdate of the new common ancestor: ";
    getline(cin, newRootBirthdate);
    
    FamilyTree newRootTree(newRootName, newRootBirthdate);
    Individual* root = newRootTree.getRoot();
    
    root->addChild(family1.getRoot());
    root->addChild(family2.getRoot());
    
    cout << "Two family trees have been connected successfully." << endl;
    return newRootTree;
}

int main() {
    vector<FamilyTree> familyTrees;
    familyTrees.emplace_back("DSA kids", "01/01/1990");

    int currentTreeIndex = 0;

    while (true) {
        cout << "\nFamily Tree Generator Menu:" << endl;
        cout << "1. Add Family Member" << endl;
        cout << "2. Visualize Family Tree" << endl;
        cout << "3. Search Person" << endl;
        cout << "4. Find Relationship" << endl;
        cout << "5. Destroy Person" << endl;
        cout << "6. Change Family Tree" << endl;
        cout << "7. Connect Two Family Trees" << endl;
        cout << "8. Select Family Tree" << endl;
        cout << "9. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string parentName, childName, childBirthdate;

            cout << "Enter parent's name: ";
            cin.ignore();
            getline(cin, parentName);
            cout << "Enter child's name: ";
            getline(cin, childName);
            cout << "Enter child's birthdate: ";
            getline(cin, childBirthdate);

            Individual* parent = familyTrees[currentTreeIndex].searchIndividual(familyTrees[currentTreeIndex].getRoot(), parentName);
            if (parent) {
                Individual* child = new Individual(childName, childBirthdate);
                familyTrees[currentTreeIndex].addChild(parent, child);
                cout << "Family member added successfully." << endl;
            } else {
                cout << "Parent not found in the selected family tree. Please check the name." << endl;
            }
        } else if (choice == 2) {
            cout << "\nVisualizing all family trees:" << endl;
            for (size_t i = 0; i < familyTrees.size(); ++i) {
                cout << "Family Tree " << (i + 1) << ": " << familyTrees[i].getRoot()->getName() << endl;
                familyTrees[i].visualizeTree(familyTrees[i].getRoot(), 0);
                cout << endl;
            }
        } else if (choice == 3) {
            string name;
            cout << "Enter the name of the person to search: ";
            cin.ignore();
            getline(cin, name);
            Individual* person = familyTrees[currentTreeIndex].searchIndividual(familyTrees[currentTreeIndex].getRoot(), name);
            if (person) {
                cout << "Person found: " << person->getName() << " (" << person->getBirthdate() << ")" << endl;
            } else {
                cout << "Person not found in the selected family tree." << endl;
            }
        } else if (choice == 4) {
            string name1, name2;
            cout << "Enter the first person's name: ";
            cin.ignore();
            getline(cin, name1);
            cout << "Enter the second person's name: ";
            getline(cin, name2);

            Individual* person1 = familyTrees[currentTreeIndex].searchIndividual(familyTrees[currentTreeIndex].getRoot(), name1);
            Individual* person2 = familyTrees[currentTreeIndex].searchIndividual(familyTrees[currentTreeIndex].getRoot(), name2);
            familyTrees[currentTreeIndex].findRelationship(person1, person2);
        } else if (choice == 5) {
            string name;
            cout << "Enter the name of the person to destroy: ";
            cin.ignore();
            getline(cin, name);
            familyTrees[currentTreeIndex].destroyPerson(familyTrees[currentTreeIndex].getRoot(), name);
            cout << name << " and their subtree have been removed." << endl;
        } else if (choice == 6) {
            familyTrees.push_back(changeFamilyTree());
        } else if (choice == 7) {
            if (familyTrees.size() < 2) {
                cout << "Not enough family trees to connect." << endl;
            } else {
                FamilyTree newFamilyTree = connectTwoFamilyTrees(familyTrees[0], familyTrees[1]);
                familyTrees.push_back(newFamilyTree);
            }
        } else if (choice == 8) {
            cout << "Select Family Tree by index (starting from 1): ";
            cin >> currentTreeIndex;
            --currentTreeIndex;  // Adjust for 0-based indexing
            if (currentTreeIndex >= familyTrees.size()) {
                cout << "Invalid selection. Please try again." << endl;
                currentTreeIndex = 0;
            }
        } else if (choice == 9) {
            break;
        } else {
            cout << "Invalid choice. Exiting..." << endl;
            break;
        }
    }

    return 0;
}
