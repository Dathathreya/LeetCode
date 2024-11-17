  void put(int key, int value) { 
             if(mp.find(key)!=mp.end()){ // key is present
                _dll* addr = mp[key];
                int cunt = addr->count;
                int val1 = addr->value;
                addr->value = value;
                _dll* head=freq[cunt].first;
                _dll* tail=freq[cunt].second; // reduce list items for count
                _dll* anxt = addr->next;
                _dll* aprv = addr->prev;
                if(aprv!=NULL)
                    aprv->next = anxt;
                if(anxt!=NULL)
                    anxt->prev = aprv;
                if((head!=NULL)&&(tail!=NULL)&&(head->prev==tail)&&(tail->next==head)){                     
                    freq.erase(key); // delete from freq that key
                }
                 addr->count+=1;
                if(freq.find( addr->count)==freq.end()){
                    
                    _dll* head1 = new DLL(-1,-1,-1,NULL,NULL);
                    _dll* tail1 =  new DLL(-1,-1,-1,NULL,NULL);
                    head1->prev=tail1;
                    tail1->next=head1;
                    _dll* hp=head1->prev;
                    head1->prev = addr;
                    hp->next = addr;
                    addr->next = head1;                    
                    addr->prev = hp;
                    freq[cunt+1] = {head1,tail1};
                }
                else{
                    _dll* head1 = freq[addr->count].first; // increase list items for count
                    _dll* tail1 = freq[addr->count].second; 
                    if(head1!=NULL)
                    {
                        _dll* hp=head1->prev;
                        head1->prev = addr;
                        hp->next = addr;
                        addr->next = head1;                    
                        addr->prev = hp;
                    }
                    freq[ addr->count] = {head1,tail1};
                }
                return ;
            }
                // forgot capacity if key is not present
                // key is not present 
                // we have to handle the case where we need to clean up least freq guy so that we have room for adding new item
                int rep = 0;
                for(auto itr: freq){
                    _dll* least=itr.second.second->next;
                    int _cnt = least->count;
                     int sz = mp.size();
                     int _key = least->key;
                     if(sz>=capacity){
                          _dll* head2=itr.second.first;
                          _dll* tail2=itr.second.second;
                          _dll* anxt = least->next;
                          _dll* aprv = least->prev;
                                if(aprv!=NULL)
                                    aprv->next = anxt;
                                if(anxt!=NULL)
                                    anxt->prev = aprv;
                                if((head2->prev==tail2)&&(tail2->next==head2)){                     
                                    freq.erase(_cnt); // delete from freq that key
                                }
                            mp.erase(_key);    
                     }
                    rep++;
                    if(rep>0){
                        break;
                    }
                }
                _dll* addr = new DLL(key,value,1,NULL,NULL);
                mp[key] = addr;
                if(freq.find(1)==freq.end()){
                    _dll* head1 = new DLL(-1,-1,-1,NULL,NULL);
                    _dll* tail1 =  new DLL(-1,-1,-1,NULL,NULL);
                    head1->prev=tail1;
                    tail1->next=head1;
                    _dll* hp=head1->prev;
                    head1->prev = addr;
                    hp->next = addr;
                    addr->next = head1;                    
                    addr->prev = hp;
                    freq[1] = {head1,tail1};
                }
                else{
                    _dll* head1 = freq[1].first; // increase list items for count
                    _dll* tail1 = freq[1].second; 
                    _dll* hp=head1->prev;
                    head1->prev = addr;
                    hp->next = addr;
                    addr->next = head1;                    
                    addr->prev = hp;
                    freq[1] = {head1,tail1};
                }
                //cout<<mp.size()<<endl;
        }
};

