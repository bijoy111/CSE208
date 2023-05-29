template <typename E> class Link
{
public:
    E element; // Value for this node
    Link *next; // Pointer to next node in list
// Constructors
    Link(const E& elemval, Link* nextval)
    {
        element = elemval;
        next = nextval;
    }
    Link(Link* nextval)
    {
        next = nextval;
    }
};
template <typename E> class LList: public List<E>
{
private:
    Link<E>* head; // Pointer to list header
    Link<E>* tail; // Pointer to last element
    Link<E>* curr; // Access to current element
    int listSize=0; // Size of list
    void init()   // Intialization helper method
    {
        curr = tail = head =new Link<E>(NULL,NULL);
        listSize = 0;
    }
public:
    LList()
    {
        init();
    }
    LList(int k,E* lists)
    {
        init();    // Constructor
        listSize=k;
        for(int i=0; i<listSize; i++)
        {
            Link<E>* traverse=new Link<E>(NULL,NULL);
            traverse->element=lists[i];
            traverse->next=NULL;
            if(head->next==NULL)
            {
                head->next=traverse;
                curr=head;
                tail=traverse;
            }
            else
            {
                tail->next=traverse;
                tail=traverse;
            }
        }
    }
    ~LList()
    {
        delete [] head;
        delete [] tail;
        delete [] curr;
    }
    void clear()
    {
        delete [] head;
        delete [] tail;
        delete [] curr;
        init();
    }
// Insert "it" at current position
    void insert(const E& it)
    {
        if(head->next==NULL)
        {
            head->next = new Link<E>(it, head->next);
            curr=head;
            tail=head->next;
        }
        else if(curr==head)
        {
            head->next = new Link<E>(it, head->next);
            curr=head;
        }
        else
        {
            curr->next = new Link<E>(it, curr->next);
        }
        if(listSize<0)listSize=0;
        listSize++;
    }
    void append(const E& it)   // Append "it" to list
    {
        tail->next = new Link<E>(it, NULL);
        if(head->next==NULL)
        {
            head=tail;
            curr=head;
        }
        tail=tail->next;
        if(listSize<0)listSize=0;
        listSize++;
    }
// Remove and return current element
    E remove()
    {
        E it;
        if(head->next==NULL) return -1;
        else if(head->next->next==NULL)
        {
            it=head->next->element;
            clear();
        }
        else if(curr->next->next==NULL)
        {
            it=curr->next->element;
            Link<E>* traverse;
            traverse=head;
            while(traverse->next!=curr)
            {
                traverse=traverse->next;
            }
            curr->next=NULL;
            tail=curr;
            curr=traverse;
        }
        else
        {
            it=curr->next->element;
            curr->next=curr->next->next;
        }
        listSize--; // Decrement the count
        return it;
    }
    E moveToStart() // Place curr at list start
    {
        curr = head;
    }
    void moveToEnd() // Place curr at list end
    {
        curr=head;
        for(int i=1; i<listSize; i++)
        {
            curr=curr->next;
        }
        //movetoPos(listSize-1);
    }
// Move curr one step left; no change if already at front
    void prev()
    {
        if (curr == head) return; // No previous element
        Link<E>* temp = head;
// March down list until we find the previous element
        while (temp->next!=curr) temp=temp->next;
        curr = temp;
    }
// Move curr one step right; no change if already at end
    void next()
    {
        if(curr->next->next==NULL) return;
        curr = curr->next;
    }
    int length()
    {
        return listSize;    // Return length
    }
// Return the position of the current element
    int currPos()
    {
        Link<E>* temp = head;
        int i;
        for (i=0; curr != temp; i++)
            temp = temp->next;
        return i;
    }
// Move down list to "pos" position
    void moveToPos(int pos)
    {
//Assert ((pos>=0)&&(pos<=cnt), "Position out of range");
        if(pos<0||pos>=listSize) return;
        curr = head;
        for(int i=0; i<pos; i++) curr = curr->next;
    }
    const E& getValue()    // Return current element
    {
        //Assert(curr->next != NULL, "No value");
        return curr->next->element;
    }
    int searchItem(const E& it)
    {
        Link<E>* traverse;
        traverse=head->next;
        while(traverse->next!=NULL)
        {
            if(traverse->element==it)
            {
                return 1;
            }
            traverse=traverse->next;
        }
        return -1;
    }
};


