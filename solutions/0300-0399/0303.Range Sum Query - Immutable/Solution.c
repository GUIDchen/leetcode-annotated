// 题目：303. 区域和检索 - 数组不可变（Range Sum Query - Immutable）
// 思路：预处理前缀和数组 s，s[i] 表示前 i 个元素之和，任意区间和由两个前缀和相减得到。
// 时间复杂度：构造 O(n)、每次查询 O(1)；空间复杂度：O(n)，保存 n+1 个前缀和。
typedef struct {  // 用结构体封装状态，判题器通过结构体指针调用各个接口
    int* s;  // 前缀和数组，长度 n+1，s[i] 表示前 i 个元素之和
} NumArray;  // 题目要求的类型名

NumArray* numArrayCreate(int* nums, int n) {  // nums：原数组；n：数组长度；返回新建的对象指针
    int* s = malloc(sizeof(int) * (n + 1));  // 多申请一位，让 s[0] 当哨兵 0，省掉下标越界的特判
    s[0] = 0;  // 空前缀的和为 0
    for (int i = 0; i < n; i++) {  // 一次遍历，逐步累加出前缀和
        s[i + 1] = s[i] + nums[i];  // 前 i+1 项之和 = 前 i 项之和 + 第 i 个元素
    }  // 构造完成
    NumArray* obj = malloc(sizeof(NumArray));  // 为结构体本身申请内存
    obj->s = s;  // 把前缀和数组挂到对象上，供后续查询复用
    return obj;  // 返回对象指针给判题器
}  // numArrayCreate 结束

int numArraySumRange(NumArray* obj, int left, int right) {  // 查询闭区间 [left, right] 的元素和
    return obj->s[right + 1] - obj->s[left];  // 两个前缀和相减，O(1) 得到区间和
}  // numArraySumRange 结束

void numArrayFree(NumArray* obj) {  // 判题器用完对象后调用，释放全部堆内存
    free(obj->s);  // 先释放结构体内部的数组
    free(obj);  // 再释放结构体本身
}  // numArrayFree 结束

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);

 * numArrayFree(obj);
*/