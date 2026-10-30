// 题目：1491. 去掉最低工资和最高工资后的工资平均值（Average Salary Excluding the Minimum and Maximum Salary）
// 思路：一次遍历求出总和、最大值与最小值，再用（总和 - 最大值 - 最小值）除以 n-2 得到平均值。
// 时间复杂度：O(n)，只需扫描数组一遍；空间复杂度：O(1)，只用常数个变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏定义：取两个数中的较大值，用三目运算符实现，避免函数调用开销
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 宏定义：取两个数中的较小值

double average(int* salary, int salarySize) {  // 返回去掉一个最低工资和一个最高工资后的平均值
    int ma = INT_MIN;  // 最大值初始化为最小整数，保证第一个元素一定能把它更新掉
    int mi = INT_MAX;  // 最小值初始化为最大整数，保证第一个元素一定能把它更新掉
    int sum = 0;  // 用来累加所有工资总和
    for (int i = 0; i < salarySize; i++) {  // 遍历数组中的每一个工资
        sum += salary[i];  // 把当前工资累加进总和
        ma = max(ma, salary[i]);  // 用当前工资更新最大值
        mi = min(mi, salary[i]);  // 用当前工资更新最小值
    }  // 循环结束，sum、ma、mi 分别保存了总和、最大值、最小值
    return (sum - mi - ma) * 1.0 / (salarySize - 2);  // 先减掉一个最小值和一个最大值，再除以 n-2；乘 1.0 把整数运算提升为浮点，避免整除截断
}  // 函数结束