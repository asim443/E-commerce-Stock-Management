#include<iostream>
#include<string>
#include<vector>
using namespace std;
int productId = 0;
class product
{
private:
	int id;
	string name;
	float price;
	int quantity;
public:
	product()
	{
		id = 0;
		name = "";
		price = 0.0;
		quantity = 0;
	}
	void input(string name, float price, int quantity)
	{
		id = productId;
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		cout << "Your product *** id is:" << id << endl;
	}
	int getId()
	{
		return id;
	}
	int getQuantity()
	{
		return quantity;
	}
	string getname()
	{
		return name;
	}
	void setQuantity(int quantity)
	{
		this->quantity = quantity;
	}
	float getprice()
	{
		return price;
	}
	void output()
	{
		cout << "-------------------------" << endl;
		cout << "Product id:" << id << endl;
		cout << "Product name:" << name << endl;
		cout << "Product Price:" << price << endl;
		cout << "Product quantity:" << quantity << endl;
		cout << "-------------------------" << endl;
	}
};
struct node
{
	product data;
	node* left;
	node* right;
	int height;
};
class avltree
{
private:
	node* root;
public:
	node* sending;
	avltree()
	{
		root = NULL;
	}
	void inorder()
	{
		inorder(root);
	}
	void inorder(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		inorder(root->left);
		root->data.output();
		inorder(root->right);
	}
	bool search(int id)
	{
		return search(root, id);
	}
	bool search(node* root, int id)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->data.getId() == id)
		{
			return true;
		}
		else if (root->data.getId() < id)
		{
			search(root->right, id);
		}
		else
		{
			search(root->left, id);
		}
	}
	int getHeight(node* n)
	{
		if (n == NULL)
		{
			return 0;
		}
		return n->height;
	}
	int getBalance(node* n)
	{
		if (n == NULL)
		{
			return 0;
		}
		return getHeight(n->left) - getHeight(n->right);
	}
	void insert(string name, float price, int quantity)
	{
		root = insert(root, name, price, quantity);
	}
	node* insert(node* root, string name, float price, int quantity)
	{
		if (root == NULL)
		{
			node* newnode = new node;
			newnode->data.input(name, price, quantity);
			newnode->left = newnode->right = NULL;
			newnode->height = 1;
			return newnode;
		}
		else if (root->data.getId() < productId)
		{
			root->right = insert(root->right, name, price, quantity);
		}
		else if (root->data.getId() > productId)
		{
			root->left = insert(root->left, name, price, quantity);
		}
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		int balance = getBalance(root);
		if (balance > 1 && productId < root->left->data.getId())
		{
			return rightRotation(root);
		}
		if (balance < -1 && productId > root->right->data.getId())
		{
			return leftRotation(root);
		}
		if (balance > 1 && productId > root->left->data.getId())
		{
			root->left = leftRotation(root->left);
			return rightRotation(root);
		}
		if (balance < -1 && productId < root->right->data.getId())
		{
			root->right = rightRotation(root->right);
			return leftRotation(root);
		}
		return root;
	}
	node* minValueNode(node* root)
	{
		node* current = root;
		while (current && current->left != NULL)
		{
			current = current->left;
		}
		return current;
	}
	void deleteproduct(int proid)
	{
		root = deleteproduct(root, proid);
	}
	node* deleteproduct(node* root, int proid)
	{
		if (!root)
		{
			return root;
		}

		// Traverse the tree to find the node to be deleted
		if (proid < root->data.getId())
			root->left = deleteproduct(root->left, proid);
		else if (proid > root->data.getId())
			root->right = deleteproduct(root->right, proid);
		else {
			// Node with only one child or no child
			if (!root->left || !root->right) {
				node* temp = root->left ? root->left : root->right;

				// No child case
				if (!temp) {
					temp = root;
					root = NULL;
				}
				else {
					*root = *temp; 
				}
				delete temp; 
			}
			else {
				node* temp = minValueNode(root->right);
				root->right = deleteproduct(root->right, temp->data.getId()); 
			}
		}
		if (!root)
			return root;
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));

		// Get the balance factor of this node to check whether this node became unbalanced
		int balance = getBalance(root);

		// If this node becomes unbalanced, then there are 4 cases

		// Left Left Case
		if (balance > 1 && getBalance(root->left) >= 0)
			return rightRotation(root);

		// Left Right Case
		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotation(root->left);
			return rightRotation(root);
		}

		// Right Right Case
		if (balance < -1 && getBalance(root->right) <= 0)
			return leftRotation(root);

		// Right Left Case
		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rightRotation(root->right);
			return leftRotation(root);
		}

		return root; // Return the (unchanged) node pointer
	}
	node* rightRotation(node* n)
	{
		node* child = root->left;
		node* childright = child->right;
		child->right = root;
		root->left = childright;
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		child->height = 1 + max(getHeight(child->left), getHeight(child->right));
		return child;
	}
	node* leftRotation(node* root)
	{
		node* child = root->right;
		node* childLeft = child->left;

		child->left = root;
		root->right = childLeft;

		// Update heights
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		child->height = 1 + max(getHeight(child->left), getHeight(child->right));

		return child;
	}
	bool update(int id,int quantity)
	{
		return update(root, id,quantity);
	}
	bool update(node* root, int id,int quantity)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->data.getId() == id)
		{
			int q = root->data.getQuantity();
			if (q >= quantity)
			{
				root->data.setQuantity(q-quantity);
				sending = root;
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (root->data.getId() < id)
		{
			update(root->right, id, quantity);
		}
		else
		{
			update(root->left, id, quantity);
		}
	}
	bool updatePlusQuantity(int id, int quantity)
	{
		return updatePlusQuantity(root, id, quantity);
	}
	bool updatePlusQuantity(node* n, int id, int quantity)
	{
		if (n== NULL)
		{
			return false;
		}
		else if (n->data.getId() == id)
		{
			n->data.setQuantity(n->data.getQuantity() + quantity);
		}
		else if (n->data.getId() < id)
		{
			updatePlusQuantity(n->right, id, quantity);
		}
		else if (n->data.getId() > id)
		{
			updatePlusQuantity(n->left, id, quantity);
		}
	}
	node sender()
	{
		return *sending;
	}
	float senderPrice()
	{
		return sending->data.getprice();
	}
};
int main()
{
	avltree avl;
	int choice;
	do
	{
		cout << "-----------------------------------------" << endl;
		cout << "Press 1 for seller account!" << endl;
		cout << "Press 2 for buyer account!" << endl;
		cout << "Press 3 to exit!" << endl;
		cout << "-----------------------------------------" << endl;
		cin >> choice;
		if (choice == 1)
		{
			//seller section
			int sellerChoice;
			do
			{
				cout << "-----------------------------------------" << endl;
				cout << "Press 1 for adding products!" << endl;
				cout << "Press 2 for showing all the products!" << endl;
				cout << "Press 3 for deleting the products!" << endl;
				cout << "Press 4 to exit!" << endl;
				cout << "-----------------------------------------" << endl;
				cin >> sellerChoice;
				if (sellerChoice == 1)
				{
					//adding the product.
					string name;
					float price;
					int quantity;
					cout << "Enter name of product:";
					cin.ignore();
					getline(cin, name);
					cout << "Enter price of a single product:";
					cin >> price;
					while (price <= 0)
					{
						cout << "Price can't be negative or equal to zero!" << endl;
						cout << "Input again:";
						cin >> price;
					}
					cout << "Enter total quantity:";
					cin >> quantity;
					while (quantity <= 0)
					{
						cout << "Quantity can't be negative or equal to zero!" << endl;
						cout << "Input again:";
						cin >> quantity;
					}
					productId++;
					avl.insert(name, price, quantity);
					cout << "Your product Id is:" << productId << endl;
				}
				else if (sellerChoice == 2)
				{
					avl.inorder();
				}
				else if (sellerChoice == 3)
				{
					cout << "Enter the product Id of the deleting product:";
					int id;
					cin >> id;
					if (id >productId)
					{
						cout << "Invalid product Id!" << endl;
					}
					else
					{
						avl.deleteproduct(id);
					}
				}
				else if (sellerChoice == 4)
				{
					break;
				}
				else
				{
					cout << "Invalid input! Try again!" << endl;
				}
			} while (sellerChoice != 4);
		}
		else if (choice == 2)
		{
			int buyerchoice;
			vector<node>cart;
			float price=0.0;
			do
			{
				cout << "-----------------------------------------" << endl;
				cout << "Press 1 to show all the products!" << endl;
				cout << "Press 2 to show the cart!" << endl;
				cout << "Press 3 to add  a product to cart!" << endl;
				cout << "Press 4 to exit!" << endl;
				cout << "Press 5 to purchase!" << endl;
				cout << "Press 6 to update a product in cart!" << endl;
				cout << "Press 7 to delete a product from cart!" << endl;
				cout << "-----------------------------------------" << endl;
				cin >> buyerchoice;
				if (buyerchoice == 1)
				{
					avl.inorder();
				}
				else if (buyerchoice == 2)
				{
					// to show all the products inside the cart.
					if (cart.size() == 0)
					{
						cout << "Cart is empty!" << endl;
					}
					else
					{
						auto it = cart.begin();
						while (it != cart.end())
						{
							(*it).data.output();
							it++;
						}
					}
				}
				else if (buyerchoice == 3)
				{
					//to purchase a product.
					int id;
					cout << "Enter the product Id:";
					cin >> id;
					while (id <= 0)
					{
						cout << "Id can't be negative or equal to zero!" << endl;
						cout << "Input again:";
						cin >> id;
					}
					if (id > productId)
					{
						cout << "Invalid product id!" << endl;
					}
					else
					{
						int quantity;
						cout << "Enter quantity:";
						cin >> quantity;
						while (quantity <=0)
						{
							cout << "Quantity can't be negative or equal to zero!" << endl;
							cout << "Input again:";
							cin >> quantity;
						}
						bool answer=avl.update(id,quantity);
						if (answer == true)
						{
							price += (avl.senderPrice()*quantity);
							cout << "Added to cart successfully!" << endl;
							cart.push_back(avl.sender());
							cart.back().data.setQuantity(quantity);
						}
						else
						{
							cout << "Quantity is very high!" << endl;
						}
					}
				}
				else if (buyerchoice == 4)
				{
					break;
				}
				else if (buyerchoice == 5)
				{
					if (price == 0)
					{
						cout << "Add a thing to cart first!" << endl;
						continue;
					}
					cout << "Your total price is:" << price <<"$" << endl;
					int p;
					cout << "Enter your money:";
					cin >> p;
					if (p < price)
					{
						cout << "Your money is less than the total price! Try again!" << endl;
						continue;
					}
					cout << "Your transaction is completed!" << endl;
					exit(0);
				}
				else if (buyerchoice == 6)
				{
					//update a product in cart.
					int id;
					cout << "Enter id of product:";
					cin >> id;
					if (id > productId)
					{
						cout << "Invalid product Id" << endl;
						continue;	
					}
					auto it = cart.begin();
					while (it != cart.end())
					{
						if ((*it).data.getId() == id)
						{
							int quantity;
							cout << "Enter the quantity to update:";
							cin >> quantity;
							while (quantity <= 0)
							{
								cout << "Quantity can't be negative or equal to zero!" << endl;
								cout << "Input again:";
								cin >> quantity;
							}
							bool answer = avl.update(id, quantity);
							if (answer == true)
							{
								price += (avl.senderPrice() * quantity);
								cout << "Added to cart successfully!" << endl;
								(it)->data.setQuantity((it)->data.getQuantity() + quantity);
								/*while (p != cart.end())
								{
									if (id == (*p).data.getId())
									{
										
										check = true;
									}
									p++;
								}
								if (check == false)
								{
									cart.push_back(avl.sender());
									cart.back().data.setQuantity(quantity);
								}*/
								
								break;
							}
							else
							{
								cout << "Quantity is very high!" << endl;
							}
						}
						it++;
					}
				}
				else if (buyerchoice == 7)
				{
					//delete a product in cart.
					if (cart.size() == 0)
					{
						cout << "Cart is empty!" << endl;
					}
					else
					{
						int id;
						cout << "Enter id of product:";
						cin >> id;
						while (id <= 0)
						{
							cout << "ID can't be negative or equal to zero!" << endl;
							cout << "Input again:";
							cin >> id;
						}
						auto it = cart.begin();
						bool check = false;
						while (it != cart.end())
						{
							if ((*it).data.getId() == id)
							{
								check = true;
								//delete that item.
								auto iter = it;
								bool pricecheck = false;
								node* upd = new node;
								while (iter+1 != cart.end())
								{
									price = true;
									upd->data = (*iter).data;
									upd->left = (*iter).left;
									upd->right = (*iter).right;
									upd->height = (*iter).height;
									cout << "deleted item price:" << upd->data.getprice() << endl;
									cout << "Deleted item quantity:" << upd->data.getQuantity() << endl;
									price -= (upd->data.getprice() * upd->data.getQuantity());
									avl.updatePlusQuantity(id,(*iter).data.getQuantity());
									auto replace = (iter + 1);
									(*iter).data = (*replace).data;
									iter++;
								}
								node last = cart.back();
								cart.pop_back();
								if (pricecheck == false)
								{
									upd->data = last.data;
									upd->left = last.left;
									upd->right = last.right;
									upd->height = last.height;
									avl.updatePlusQuantity(id, upd->data.getQuantity());
									price -= (last.data.getprice() * last.data.getQuantity());
								}
								cout << "Deleted successfully!" << endl;
								break;
							}
							it++;
						}
						if (check == false)
						{
							cout << "Product with this id is not found!" << endl;
						}
					}
				}
				else
				{
					cout << "Invalid input! Try again!" << endl;
				}
			} while (buyerchoice != 4);
		}
		else if (choice == 3)
		{
			break;
		}
		else
		{
			cout << "Invalid input! Try again!" << endl;
		}
	} while (choice != 3);
}
