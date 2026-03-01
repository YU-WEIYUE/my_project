#include <stdio.h>
#include <string.h>  // 对应C++的cstring，用于memset

// 全局变量（和原代码保持一致）
int n, a[90], b[90], c[90], f[90], d = 0, len_a, len_b = 1, len_c = 1, len_ans, m = 1;

int main() {
    scanf("%d", &n);
    b[0] = 1; 
    for(int i = 1; i <= n; i++) { // 计算i的阶乘（基于i-1的阶乘）
        len_a = 0; // 存储i的位数
        int p = i;
        // 把i拆解到a数组（低位在前），和原逻辑一致
        while(p > 0) {
            a[len_a++] = p % 10;
            p /= 10;
        }
        // 大数乘法：a(i) * b(i-1!) = c(i!)
        for(int j = 0; j < len_a; j++)
            for(int k = 0; k <= len_b; k++)
                c[j + k] += a[j] * b[k];
        
        // 乘法进位处理
        for(int j = 0; j < len_c; j++)
            if(c[j] > 9) {
                c[j + 1] += c[j] / 10;
                c[j] %= 10;
            }
        
        // 检查最高位是否需要进位，更新len_c
        if(c[len_c]) len_c++;
        
        // 保存长度，更新最大长度m
        len_ans = len_b;
        len_b = len_c;
        m = (m > len_c) ? m : len_c; // C没有max函数，用三元运算符替代
        
        // 把c数组（i!）复制到b数组，作为下一轮的i-1!
        for(int k = len_c - 1; k >= 0; k--)
            b[k] = c[k];
        
        len_c = len_a + len_ans;
        memset(c, 0, sizeof(c)); // 清零c数组，准备下一次乘法
        
        // 大数加法：把当前i!（b数组）累加到结果f数组
        for(int j = 0; j < m; j++) {
            f[j] += b[j];
            if(f[j] > 9) { // 原代码标注的易错点：不能用f[j+1]++
                f[j + 1] += f[j] / 10;
                f[j] %= 10;
            }
        }
    }
    
    // 去掉前导零（找到最高位）
    while(!f[m] && m > 0) m--;
    
    // C++的cout替换为C的printf，倒序输出结果
    for(int i = m; i >= 0; i--)
        printf("%d", f[i]);
    
    return 0;
}