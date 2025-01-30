#ifndef _utl_h
#define _utl_h

class average_saver {
    public:
    average_saver(int length,int thr);
    void save(int value);
    bool get();
    private:
    int idx = 0;
    int thr;
    int len;
    int val[1000];
};

average_saver::average_saver(int length,int thr){
    this -> len = length;
    this -> thr = thr;
    for(int i = 0; i < len; i++){
        val[i] = 0;
    }
}

void average_saver::save(int value){
    val[idx] = value;
    idx = (idx + 1) % len;
}

bool average_saver::get(){
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += val[i];
    }
    return sum > thr;
}

#endif