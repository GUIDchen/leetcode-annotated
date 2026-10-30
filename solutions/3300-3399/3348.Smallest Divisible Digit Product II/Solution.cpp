// 题目：3348. 最小可整除数位乘积 II（Smallest Divisible Digit Product II）
// 思路：把 t 分解为 2/3/5/7 的幂，用贪心折算成最少的数字（8、9、6、4、2、3、5、7），再从右往左尝试抬高某一位，后缀用最小数字排列补齐。
// 时间复杂度：O(n * 10)（n 为 num 长度，素因子指数只与 t 有关）；空间复杂度：O(1)，只维护常数大小的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestNumber(string num, long long t) {  // num：下界字符串（结果必须不小于它）；t：数位乘积必须是 t 的倍数
        int required[4]{};  // required：t 分解后 2、3、5、7 各自的指数
        if (!factorize(t, required)) {  // 分解失败说明 t 含 2/3/5/7 之外的素因子
            return "-1";  // 任何数位乘积都只含这四个素因子，故必然无解
        }  // 结束可行性判断
        int need[10]{};  // need：用尽量少的数字表示上述指数时各数字的个数
        toDigits(required, need);  // 把素因子指数贪心折算成每个数字需要使用几个
        if (sum(need, 10) > (int) num.size()) {  // 所需位数比原数长度还长
            return construct(need);  // 只能在更高位构造：用最小数字排列并在前面补 1
        }  // 结束位数判断

        int prefix[4]{};  // prefix：num 已固定前缀的素因子指数累计值
        for (char ch : num) {  // 一次遍历累加整个字符串的素因子指数
            add(prefix, DIGIT_PRIMES[ch - '0']);  // 把该数字的素数分解结果加到前缀上
        }  // 结束累加
        int firstZero = num.find('0');  // 找到第一个 0：0 会让整个数位乘积变成 0，是天然的不可用位置
        if (firstZero == (int) string::npos) {  // 字符串中不存在 0
            firstZero = num.size();  // 视作 0 出现在末尾之后，整串都可以保留
            if (isSubset(required, prefix)) {  // num 自身的素因子已经覆盖 t 的全部要求
                return num;  // 原数本身就是最小答案，无需修改
            }  // 结束覆盖判断
        }  // 结束无零分支

        int n = num.size();  // 原数长度
        for (int i = n - 1; i >= 0; --i) {  // 从最右位向左扫描：寻找「抬高第 i 位、后缀补最小」的最优切点
            subtractInPlace(prefix, DIGIT_PRIMES[num[i] - '0']);  // 先把第 i 位自身从累计值里去掉，prefix 变成 num[0..i-1] 的指数
            int space = n - 1 - i;  // 位置 i 之后还可以自由填写的位数
            if (i > firstZero) {  // 第一个 0 右侧的位置不能改（改了会出现 0 或破坏下界），只能继续左移
                continue;  // 跳到更左边的位置
            }  // 结束跳过判断
            for (int bigger = num[i] - '0' + 1; bigger < 10; ++bigger) {  // 枚举把第 i 位换成更大的数字，这样整体一定仍大于等于 num
                int tmp[4]{}, suffix[10]{};  // tmp：还缺的素因子指数；suffix：后缀各数字的安排
                subtract(required, prefix, tmp);  // 已固定的前缀吃掉一部分需求，剩下的必须由新第 i 位和后缀承担
                subtractInPlace(tmp, DIGIT_PRIMES[bigger]);  // 新第 i 位的数字也能承担一部分素因子
                toDigits(tmp, suffix);  // 把剩余指数折算成最少的后缀数字
                if (sum(suffix, 10) <= space) {  // 剩余需求能在后缀位数预算内放下（放不满的用 1 补齐）
                    return num.substr(0, i) + char('0' + bigger) + string(space - sum(suffix, 10), '1') + construct(suffix);  // 组装答案：原前缀 + 抬高的第 i 位 + 补若干个 1 + 最小数字排列
                }  // 结束可行性判断
            }  // 结束 bigger 枚举
        }  // 结束从右往左的扫描
        int ext[10]{};  // ext：原长度内无解，需要加一位时各数字的个数
        toDigits(required, ext);  // 只用 t 的需求折算成最少的数字组合
        return string(n + 1 - sum(ext, 10), '1') + construct(ext);  // 加长一位：多出来的高位用 1 填满（1 不改变乘积），后面接最小数字排列
    }  // 结束主方法

private:  // 以下都是内部辅助函数，对外不可见
    static constexpr int DIGIT_PRIMES[10][4] = {  // 数字 0~9 分别对应的 (2,3,5,7) 指数常量表，O(1) 查表
        {0, 0, 0, 0},  // 数字 0：无法参与乘积，这里占位为全 0
        {0, 0, 0, 0},  // 数字 1：乘积的单位元，不含任何素因子
        {1, 0, 0, 0},  // 数字 2 = 2^1
        {0, 1, 0, 0},  // 数字 3 = 3^1
        {2, 0, 0, 0},  // 数字 4 = 2^2
        {0, 0, 1, 0},  // 数字 5 = 5^1
        {1, 1, 0, 0},  // 数字 6 = 2 * 3
        {0, 0, 0, 1},  // 数字 7 = 7^1
        {3, 0, 0, 0},  // 数字 8 = 2^3
        {0, 2, 0, 0},  // 数字 9 = 3^2
    };  // 常量表结束

    bool factorize(long long t, int counts[4]) {  // 把 t 分解到 2、3、5、7 上；能除干净返回 true
        int primes[4] = {2, 3, 5, 7};  // 数位乘积只可能由这四个素因子组成
        for (int i = 0; i < 4; ++i) {  // 逐个素因子试除
            while (t % primes[i] == 0) {  // 还能整除就一直除下去
                t /= primes[i];  // 除掉一个素因子
                ++counts[i];  // 对应指数加一
            }  // 结束试除循环
        }  // 结束素因子循环
        return t == 1;  // 除到 1 说明 t 只含这四个素因子
    }  // 结束分解

    void toDigits(const int primes[4], int digits[10]) {  // 把素因子指数折算成每个数字的最少使用个数
        int count8 = primes[0] / 3;  // 每 3 个 2 用一个大数字 8 表示最省位
        int remaining2 = primes[0] % 3;  // 除完后剩下的 2 的指数（0~2）
        int count9 = primes[1] / 2;  // 每 2 个 3 用一个 9 表示最省位
        int count3 = primes[1] % 2;  // 除完后剩下的 3 的指数（0~1）
        int count4 = remaining2 / 2;  // 两个 2 合成一个 4
        int count2 = remaining2 % 2;  // 还剩一个 2 就用数字 2 承担
        int count6 = 0;  // 数字 6 的个数，先置 0
        if (count2 == 1 && count3 == 1) {  // 同时剩下一个 2 和一个 3，合并成一个 6 可以省一位
            count2 = 0;  // 2 已经并入 6
            count3 = 0;  // 3 已经并入 6
            count6 = 1;  // 使用一个数字 6
        }  // 结束合并
        if (count3 == 1 && count4 == 1) {  // 剩一个 3 和一个 4 时，拆成 2 与 6 位数更少（4 * 3 = 2 * 6）
            count2 = 1;  // 数字 2 承担一个因子 2
            count6 = 1;  // 数字 6 承担 2 * 3
            count3 = 0;  // 3 已经并入 6
            count4 = 0;  // 4 已经被拆解掉
        }  // 结束拆分
        int vals[10] = {0, 0, count2, count3, count4, primes[2], count6, primes[3], count8, count9};  // 按数字 0~9 汇总各自的使用个数
        for (int i = 0; i < 10; ++i) {  // 拷贝到调用方传入的输出数组
            digits[i] = vals[i];  // 逐项赋值
        }  // 结束拷贝
    }  // 结束折算

    string construct(const int digits[10]) {  // 把各数字的使用个数拼成字典序最小的字符串
        string res;  // 结果串，初始为空
        for (int d = 2; d < 10; ++d) {  // 从 2 到 9 依次输出：位数相同的前提下升序排列即字典序最小
            res.append(digits[d], char('0' + d));  // 追加 digits[d] 个字符 d
        }  // 结束拼接
        return res;  // 返回拼好的字符串
    }  // 结束构造

    bool isSubset(const int a[4], const int b[4]) {  // 判断需求 a 是否已经被 b 完全覆盖
        for (int i = 0; i < 4; ++i) {  // 逐个素因子比较指数
            if (b[i] < a[i]) {  // 某个素因子的指数不够
                return false;  // 不满足覆盖关系
            }  // 结束判断
        }  // 结束循环
        return true;  // 所有素因子都够用
    }  // 结束覆盖判断

    void subtract(const int a[4], const int b[4], int res[4]) {  // 计算缺口：逐项取 max(0, a - b)
        for (int i = 0; i < 4; ++i) {  // 逐个素因子相减
            res[i] = max(0, a[i] - b[i]);  // 只保留正的缺口，多余部分视为已经满足
        }  // 结束循环
    }  // 结束相减

    void subtractInPlace(int a[4], const int b[4]) {  // 原地扣除 b 的指数
        for (int i = 0; i < 4; ++i) {  // 逐个素因子扣除
            a[i] = max(0, a[i] - b[i]);  // 扣除后夹到 0，避免出现负数
        }  // 结束循环
    }  // 结束原地相减

    void add(int a[4], const int b[4]) {  // 把 b 的指数累加到 a 上
        for (int i = 0; i < 4; ++i) {  // 逐个素因子累加
            a[i] += b[i];  // 指数直接相加
        }  // 结束循环
    }  // 结束累加

    int sum(const int* a, int n) {  // 求数组前 n 项之和，这里用来统计总位数
        int s = 0;  // 累加器
        for (int i = 0; i < n; ++i) {  // 遍历前 n 项
            s += a[i];  // 累加当前项
        }  // 结束循环
        return s;  // 返回合计值
    }  // 结束求和
};  // 结束类
