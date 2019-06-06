inline
double Qsort::getArr(int i){
    return (arr_[i]);
}

inline
void Qsort::setArr(int i, double val){
    arr_[i] = val;
}

inline
size_t Qsort::getIndex(int i){
    return (index_[i]);
}

inline
void Qsort::setIndex(int i, size_t val){
    index_[i] = val;
}

inline
size_t Qsort::getSize(){
    return (size_);
}

inline
void Qsort::setSize(size_t i){
    size_ = i;
}


inline
void Qsort::quickSort (int left, int right){
    if (left < right){

        int pi = partition(left, right);

        /* recursion */
        quickSort(left, pi - 1);
        quickSort(pi + 1, right);
    } 
}

inline
int Qsort::partition (int left, int right){
    double pivot = getArr(right);
    int i = (left - 1);
 
    for (int j = left; j <= right-1; j++){
        if (getArr(j) >= pivot){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);
    return (i + 1);
}

inline
void Qsort::swap(int left, int right){
    double temp = getArr(left);
	setArr(left, getArr(right));
    setArr(right, temp);

    size_t tempIndex = getIndex(left);
    setIndex(left, getIndex(right));
    setIndex(right, tempIndex); 
}