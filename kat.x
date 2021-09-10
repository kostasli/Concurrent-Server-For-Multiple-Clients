struct Y_arr{
    int Y<25>;
    int Y_size;
};

struct max_min{
    int max;
    int min;
};

struct a_mul_Y{
    int Y<25>;
    int Y_size;
    float a;
};

struct aY{
  float prod<25>;
};

  program CONCURRENT_SERVER_PROG{
    version CONCURRENT_SERVER_VER{
       float average(Y_arr)=1;
       max_min maxmin(Y_arr)=2;
       aY product(a_mul_Y)=3;
    }=1;
  }=0x23450001;