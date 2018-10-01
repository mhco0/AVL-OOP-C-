# AVL-OOP-C-
This is a functional AVL in c++ based in the Geeksforgeeks algorithm. 

##Methods
*Insert
This method inserts a key into the AVL.

*Search
This method searchs a Key that was passed as a argument and returns true if the key was founded and false otherwise.

*Remove
This method remove a element from the AVL.

*Empty
This method is boolean. If the AVL is empty he returns true,if isn't he returns false.

*Show
This method return a print of the AVL tree in pos , in or pre order:

The argument must be a enum class order.

```c++
  int main(void){
    avl<int> t;
  	t.insert(1);
	  t.insert(2);
	  t.insert(3);

	  t.show(order::preorder);
    t.show(order::inorder);
    t.show(order::posorder);
    
    return 0;
  }
```
