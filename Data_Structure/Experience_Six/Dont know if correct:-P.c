/* Quick Sort Demo from book.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 * 
 * This formula, basically, copied from book. Don't know if correct.
 * The book code sucks, I found a better one.
 */
void QuickSort(int numbers[], int lowMark, int highMark, int size){
    if (lowMark < highMark){
        int tempHighMark = highMark;
        int flag = lowMark;
        while (lowMark < highMark){
            while (lowMark < highMark && numbers[highMark] >= numbers[flag]){
                highMark --;
            }
            if (lowMark == flag){
                flag = highMark;
            }
            swap(&numbers[lowMark],&numbers[highMark]);
            while (lowMark < highMark && numbers[lowMark] <= numbers[flag]){
                lowMark ++;
            }
            if (highMark == flag){
                flag = lowMark;
            }
            swap(&numbers[lowMark],&numbers[highMark]);
        }
        QuickSort(numbers, 0, flag-1, size);
        QuickSort(numbers, flag+1, tempHighMark, size);
    } else {
        return;
    }
}
