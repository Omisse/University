#ifndef S3L7_NODE_TPP
#define S3L7_NODE_TPP

namespace prog_s3 {
    template<typename T>    
    struct Node {
        T value = T();
        Node* next = this;
        Node* previous = this;

        Node(): value(), next(this), previous(this) {};

        Node(T val, Node* next = nullptr, Node* prev = nullptr):
            value(val), next(next), previous(prev) {}

        
    };
}


#endif //S3L7_NODE_TPP