// 题目：2299. 强密码检验器 II（Strong Password Checker II）
// 思路：一次遍历，用位掩码标记小写、大写、数字、特殊字符四类是否出现，同时比较相邻字符排除连续重复；长度不足 8 直接判负。
// 时间复杂度：O(n)，password 只扫一遍；空间复杂度：O(1)，只用常数个变量。
bool strongPasswordCheckerII(char* password) {  // 判断密码是否满足强密码的全部条件
    int n = strlen(password);  // 先取长度，后面多处要用
    if (n < 8) {  // 条件一：长度至少 8 位
        return false;  // 长度不够，直接返回假
    }  // 长度检查结束
    int mask = 0;  // 四类字符的出现标记：bit3 小写、bit2 大写、bit1 数字、bit0 其他
    char prev = ' ';  // 记录前一个字符，用于判断是否存在连续相同的字符
    for (int i = 0; i < n; i++) {  // 逐位扫描密码
        if (prev == password[i]) {  // 条件二：与前一字符相同即出现连续重复
            return false;  // 有相邻重复，直接返回假
        }  // 相邻重复检查结束
        if (islower(password[i])) {  // 分类统计：先看是不是小写字母
            mask |= 0b1000;  // 置上小写字母对应的 bit3
        } else if (isupper(password[i])) {  // 否则看是不是大写字母
            mask |= 0b100;  // 置上大写字母对应的 bit2
        } else if (isdigit(password[i])) {  // 再看是不是数字
            mask |= 0b10;  // 置上数字对应的 bit1
        } else {  // 剩下的都归为特殊字符
            mask |= 0b1;  // 置上特殊字符对应的 bit0
        }  // 字符分类结束
        prev = password[i];  // 更新 prev，供下一轮比较相邻字符
    }  // 扫描结束
    return mask == 0b1111;  // 四类字符都出现过（0b1111）才算强密码
}  // 函数结束