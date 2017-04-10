//队列的链式存储结构
typedef struct QNdoe{
    QElemType data;
    struct QNdoe* next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;    //队头指针
    QueuePtr rear;     //队尾指针
}LinkQueue;




//链队的初始化

Statue InitQueue (LinkQueue &Q){
    //构造一个空队列Q
    Q.front = Q.rear = new QNode;
    Q.front -> next = NULL;
    return OK;
}

//链队入队

Status EnQueue (LinkQueue &Q , QElemtype e){
    //插入元素e为Q的新的队尾元素
    p = new QNode;
    p -> data = e;
    p -> next = NULL;
    Q.rear -> next = p;
    Q.rear = p;
    return OK;
}

//链队出队

Status DeQueue (LinkQueue &Q , QElemtype &e){
    //删除Q的队头元素，用e返回其值
    if (Q.front == Q.rear){
        return ERROR;
    }
    p = Q.front -> next;
    e = p -> data;
    Q.front -> next = p -> next;
    if (Q.rear == p){
        Q.rear = Q.front;
    }
    delete p;
    return OK;
}


//销毁链队

Status DestoryQueue (LinkQueue &Q){
    while (Q.front){
        Q.rear = Q.front -> next;
        delete Q.front;
        Q.front = Q.rear;
    }
    return OK;
}


//取队头元素

SElemType GetHead (LinkQueue Q){
    //返回Q的队头元素，不修改队头指针
    if (Q.front != Q.rear){
        return Q.front -> next -> data;
    }
}