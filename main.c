#include <linux/module.h>

static int __init helloworld_init(void)
{
  pr_info("hello world\n");
  return 0;
}

static void __exit helloworld_cleanup(void)
{
  pr_info("goodbye world\n");
}

module_init(helloworld_init);
module_exit(helloworld_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("A SIMPLE HELLO WORLD");
MODULE_INFO(board, "beaglenone black EEV A5");

