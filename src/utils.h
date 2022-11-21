// Map-like function which constraints the input and output values
int getPercent(int x, int in_min, int in_max, int out_min, int out_max) {
    if (x > in_max) {
        return out_max;
    }
    else if (x < in_min) {
        return out_min;
    } 
    else {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}