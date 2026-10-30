// 题目：2037. 使每位学生都有座位的最少移动次数（Minimum Number of Moves to Seat Everyone）
// 思路：排序后按位配对。两组数各自升序排列后，第 i 小的座位配第 i 小的学生，此时总位移最小；答案为 ∑|seats[i] - students[i]|。
// 时间复杂度：O(n log n)，两次快排；空间复杂度：O(log n)，qsort 的递归栈开销（原地排序，没有额外数组）。
int cmp(const void* a, const void* b) {  // qsort 的比较函数：把 void* 转回 int*，按升序比较
    return *(int*) a - *(int*) b;  // 返回两元素之差，符号决定升降序（这里由小到大）
}  // 结束 cmp

// 判题器直接调用该函数，源文件是题目片段，因此没有 main 与 #include。
int minMovesToSeat(int* seats, int seatsSize, int* students, int studentsSize) {  // seats 是座位坐标数组，students 是学生初始位置数组，返回最少总移动次数
    qsort(seats, seatsSize, sizeof(int), cmp);  // 座位升序排序
    qsort(students, studentsSize, sizeof(int), cmp);  // 学生位置升序排序
    int ans = 0;  // 累计总移动次数
    for (int i = 0; i < seatsSize; i++) {  // 排序后按位配对，第 i 个学生去第 i 个座位
        ans += abs(seats[i] - students[i]);  // 两者距离即该学生需要的移动步数
    }  // 结束累加循环
    return ans;  // 返回最少移动次数
}  // 结束 minMovesToSeat