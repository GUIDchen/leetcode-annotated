// 题目：2546. 执行逐位运算使字符串相等（Apply Bitwise Operations to Make Strings Equal）
// 思路：只要两个串「是否含 1」的状态一致即可互相转换；操作只能在有 1 的前提下改变 0，含 1 时两个串可以双向变换。
// 时间复杂度：O(n)，各自找到第一个 1 即停；空间复杂度：O(1)。
bool makeStringsEqual(char* s, char* target) {  // 判断 s 能否通过逐位运算变成 target
    int count = 0;  // 计数：s 中是否有 1、target 中是否有 1，各贡献 1
    for (int i = 0; s[i]; i++) {  // 扫描 s，以字符串结尾的 '\0' 作为终止条件
        if (s[i] == '1') {  // 找到任意一个 1 就说明 s 含有 1
            count++;  // 计数加一
            break;  // 只需判断是否存在，找到即可提前结束
        }  // 结束判断
    }  // 结束对 s 的扫描
    for (int i = 0; target[i]; i++) {  // 再用同样的方式扫描 target
        if (target[i] == '1') {  // target 中也出现了一个 1
            count++;  // 计数加一
            break;  // 找到即可提前结束
        }  // 结束判断
    }  // 结束对 target 的扫描
    return !(count & 1);  // count 为 0（都没 1）或 2（都有 1）时相等，count 为 1 说明只有一边有 1，无法转换
}  // 函数结束（源文件末尾无换行，保持原样）