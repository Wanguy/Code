//队列的顺序存储结构

#define MAXQSIZE 100        //队列可达到最大长度
typedef struct{
    QElemType* base;        //存储空间的基地址
    int front;              //头指针
    int rear;               //尾指针
}SqQueue;






//初始化循环队列

Status InitQueue (SqQueue &Q){
    //构造一个空队列
    Q.base = new QElemType[MAXQSIZE];
    if (!Q.base){
        exit(OVERFLOW);
    }
    Q.front = Q.rear = 0;
    return OK;
}

//循环队列的长度

int QueueLength (SqQueue Q){
    //返回Q的元素个数，即队列长度
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//循环队列入队

Status EnQueue (SqQueue &Q , QElemType e){
    //插入元素e为Q的新队尾元素
    if ((Q.rear + 1) % MAXQSIZE == Q.front){
        return ERROR;
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

//循环列队出队

Status DeQueue (SqQueue &Q , QElemType &e){
    //删除Q的队头元素，用e返回其值
    if (Q.front == Q.rear){
        return ERROR;
    }
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

//取循环列队的队头元素

SElemType GetHead (SqQueue Q){
    //返回Q的队头元素，不修改队头指针
    if (Q.front != Q.rear){
        return Q.base[Q.front];
    }
}