// 题目：1700. 无法吃午餐的学生数量（Number of Students Unable to Eat Lunch）
// 思路：先统计喜欢 0 型、1 型三明治的学生人数，再按栈顶顺序模拟发放；一旦栈顶类型没有学生喜欢，队伍就卡死，剩余学生都吃不到。
// 时间复杂度：O(n + m)，n 为学生数、m 为三明治数；空间复杂度：O(1)，只用长度为 2 的计数数组。
int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize) {  // 返回最终吃不到午餐的学生人数
    int count[2] = {0};  // count[0] 记录喜欢 0 型的学生数，count[1] 记录喜欢 1 型的学生数
    for (int i = 0; i < studentsSize; i++) {  // 遍历所有学生，先做一次人数统计
        count[students[i]]++;  // students[i] 只会是 0 或 1，直接拿它当下标把对应计数加一
    }
    for (int i = 0; i < sandwichesSize; i++) {  // 按栈的顺序逐个尝试发放，i 指向当前栈顶三明治
        int j = sandwiches[i];  // 当前栈顶三明治的类型（0 或 1）
        if (count[j] == 0) {  // 没有任何学生喜欢这一型，说明队伍无法再前进
            return count[j ^ 1];  // 剩下的人全是另一型偏好，j ^ 1 就是把它取反
        }
        count[j]--;  // 有一位喜欢该型的学生领走三明治并离开队伍，计数减一
    }
    return 0;  // 三明治全部发完，说明每个学生都吃到了
}