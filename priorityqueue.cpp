//
// Created by Auboni Poddar on 2019-11-13.
//

#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
#include <math.h>

PriorityQueue::PriorityQueue(std::size_t max_size) :
        nodes_(max_size + 1, KeyValuePair()),
        max_size_(max_size),
        size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {

    // TODO: complete this function
    size_ = size_ + 1;

    nodes_.at(size_ - 1) = kv;
    //  for (size_t i = 0; i < size_; i++) {
    //      std::cout << nodes_.at(i).first << " " << std::endl ;
    //  }
    // std::cout << "size " << size_ -1 ;
    int parent = floor((size_ - 1 - 1) / 2);

    if (size_ == 1) {
        parent = floor((size_ - 1 ) / 2);
    }
    if(nodes_.at(size_ -  1).first < nodes_.at(parent).first){
        // std::cout << "size " << size_ -1 ;
        heapifyUp(size_ - 1);
        // std::cout << "size " << size_ -1 ;
    }
}

KeyValuePair PriorityQueue::min() {
    return nodes_.at(0);
}

KeyValuePair PriorityQueue::removeMin() {
    KeyValuePair min = nodes_.at(0);
    nodes_.at(0) = nodes_.at(size_ - 1);
    size_ = size_ - 1;
    //nodes_.pop();
    if (nodes_.at(0).first > nodes_.at(1).first || nodes_.at(0).first > nodes_.at(2).first){
        heapifyDown(0);
    }
    std::cout << "min = " << min.first << std::endl;
    return min;
    // TODO: complete this function
}

bool PriorityQueue::isEmpty() const {
    if (size_ == 0){
        return true;
    } else {
        return false;
    }
}

size_t PriorityQueue::size() const {
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i-1];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(((i - 2) / 2) + 1);
        }
        if ((2 * (i-1) + 2) <= size_) {
            node["leftChild"] = std::to_string(2 * (i-1) + 2);
        }
        if ((2 * (i-1)  + 3) <= size_) {
            node["rightChild"] = std::to_string(2 * (i-1) + 3);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    //for (int i = 0; i < size_; i++) {
    //  std::cout << nodes_.at(i).first << " ";
    //}
    //std::cout << std::endl;
    size_t temp = i;
    while( temp > 0 && nodes_.at(temp).first < nodes_.at(floor((temp - 1)/2)).first) {
        KeyValuePair tempo = nodes_.at(floor((temp - 1)/2));
        nodes_.at(floor((temp - 1)/2)) = nodes_.at(temp);
        nodes_.at(temp) = tempo;
        temp = floor((temp - 1)/2);


    }
    //for (int i = 0; i < size_; i++) {
    //  std::cout << nodes_.at(i).first << " ";
    //}
    // std::cout << std::endl;

    // TODO: complete this function
}

void PriorityQueue::heapifyDown(size_t i) {
    // 2 *


    int temp = i;
    while((2 *temp + 1 < size_ && (nodes_.at(temp).first > nodes_.at(2 * temp + 1).first)) || (2 *temp + 2 < size_ && nodes_.at(temp).first > nodes_.at(2 * temp +2).first)){
        std::cout << "before";
        for(int i = 0; i < size_ ; i++){
            std::cout <<  nodes_.at(i).first << " ";
        }
        std::cout << std::endl;

        if((2*temp + 2 < size_) && nodes_.at(2 * temp + 1).first < nodes_.at((2 * temp)+ 2).first){

            KeyValuePair leftkey = nodes_.at(2 * temp + 1);
            nodes_.at(2 * temp + 1 ) = nodes_.at(temp);
            nodes_.at(temp) = leftkey;
            temp = 2 * (temp) + 1;

        } else if((2*temp + 2 < size_) && nodes_.at(2 * temp + 1).first > nodes_.at((2 * temp)+ 2).first) {
            KeyValuePair rightkey = nodes_.at(2 * temp + 2);
            nodes_.at(2 * temp + 2) = nodes_.at(temp);
            nodes_.at(temp) = rightkey;
            temp = 2 * (temp) + 2;

        } else {
            KeyValuePair leftkey = nodes_.at(2 * temp + 1);
            nodes_.at(2 * temp + 1) = nodes_.at(temp);
            nodes_.at(temp) = leftkey;
            temp = 2 * (temp) + 1;
        }
        std::cout << "after";
        for(int i = 0; i < size_ ; i++){
            std::cout << nodes_.at(i).first << " ";
        }
        std::cout << std::endl;
    }

    // TODO: complete this function
}

void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function
}

Key PriorityQueue::getKey(size_t i) {
    return nodes_.at(i).first;
}
