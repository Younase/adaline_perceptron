#include <stdio.h>
#include <stdlib.h>

float weights[] = {0.0, 1.0, -1.0};
float bias = 1;
float learning_rate = 1;
int num_epochs=500;
#define NUM_IN 2
int flag=0;

#define DATA_LEN 4
int inputs[DATA_LEN][NUM_IN] = {{0,0},{0,1},{1,0},{1,1}};
int outputs[]={0,1,1,1};

int activation(float);
float predict(int[]);
void update(int[], int);

int main(void) {
    //training start
    for (int i = 0; i < num_epochs; ++i) {
        flag=0;
        for (int j=0; j< DATA_LEN; j++){
            printf("%i\t%i\t", inputs[j][0],inputs[j][1]);
            float ans=predict(inputs[j]);
            printf("%d\n", activation(ans));
            if (activation(ans) != outputs[j]){
                flag=1;
                update(inputs[j],outputs[j]);

            }
        }
        printf("\n");
        if (flag==0){
            printf("weights not modified\nnum training epochs:%i\n",i);
            exit(0);
        }
    }

}

int activation(float x) {
    if (x < 0.5)
        return 0;
    else
        return 1;
}

float predict(int x[]) {
    // dot product
    float dot_product = 0.0;
    dot_product = dot_product + (weights[0] * bias);
    for (int i=0; i<NUM_IN;i++){
        dot_product = dot_product + (weights[i+1] * x[i]);
    }
    // return perdiction
    //int ans = activation(dot_product);
    int ans = dot_product;
    return ans;
}

void update(int x[], int answer) {
    float prediction = predict(x);
    // calculate error
    printf("float error=%f\n",(float)answer-prediction);
    int int_error = answer - prediction;
    float error = (float)int_error;
    // calculate gradient
    float gradient[NUM_IN+1];
    //bias
    gradient[0] = error * bias * learning_rate;
    weights[0] = weights[0] + gradient[0];
    //other connections
    for (int i=0;i<NUM_IN;i++){
        gradient[i+1] = error * (float)x[i] * learning_rate;
        weights[i+1] = weights[i+1] + gradient[i+1];

    }
    printf("UPDATING WEIGHTS\n");
    for (int i=0;i<NUM_IN+1;i++){
        printf("%f\t",weights[i]);
    }
    printf("\n");

}
