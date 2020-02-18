
#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define BUFFER_SIZE 1024


/* Define device_buffer and other global data structures you will need here */
int open_count = 0;
int close_count = 0;

static char* device_buffer;
ssize_t pa2_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
		int bytesRead;
	int bytesToRead;
	int maxBytesRead = BUFFER_SIZE-*offset;
	if(maxBytesRead > length){
		bytesToRead = length;
	} else {
		bytesToRead = maxBytesRead;
	}
	if(bytesToRead == 0){
	printk(KERN_ALERT "END OF DEVIE \n");
	}
	bytesRead = bytesToRead - copy_to_user(buffer,device_buffer+*offset, bytesToRead); 
	
	printk(KERN_ALERT "bytes read: %d", bytesRead);
	*offset += bytesRead;
	printk(KERN_ALERT "Current offset location after read: %d", *offset);

	return bytesRead;
}



ssize_t pa2_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
	int bytesWrite;
	int bytesToWrite;
	int maxBytesWrite = BUFFER_SIZE-*offset;
	if(maxBytesWrite > length){
		bytesToWrite = length;
	} else {
		bytesToWrite = maxBytesWrite;
	}
	
	bytesWrite = bytesToWrite - copy_from_user(device_buffer+*offset, buffer, bytesToWrite); 
	printk(KERN_ALERT "bytesToWrite %d", bytesToWrite);
	printk(KERN_ALERT "bytes written: %d", bytesWrite);
	*offset += bytesWrite;
	printk(KERN_ALERT "Current offset location after write: %d", *offset);
	return bytesWrite;
}


int pa2_char_driver_open (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	open_count++;
	printk(KERN_ALERT "file has been opened %d", open_count);
	return 0;
}

int pa2_char_driver_close (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	close_count++;
	printk(KERN_ALERT "file has been closed %d", close_count);
	return 0;
}

loff_t pa2_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
	printk(KERN_ALERT "inside seek");

	loff_t *curr_pos = 0;
	/* Update open file position according to the values of offset and whence */
	if(whence == 0){
		curr_pos = offset;
	} else if(whence == 1){
		curr_pos = pfile->f_pos+offset;
	} else if(whence == 2){
		curr_pos = BUFFER_SIZE-offset;
	}
	if(curr_pos >= BUFFER_SIZE){
		printk(KERN_ALERT "End of the buffer");
		curr_pos = BUFFER_SIZE;
	} else if(curr_pos < 0){
		printk(KERN_ALERT "before the start of the file");
		curr_pos = 0;
	}
	pfile->f_pos = curr_pos;
	return curr_pos;
}

struct file_operations pa2_char_driver_file_operations = {

	.owner   = THIS_MODULE, 
	.open = pa2_char_driver_open,
	.release = pa2_char_driver_close, 
	.llseek = pa2_char_driver_seek, 
	.read = pa2_char_driver_read,
	.write = pa2_char_driver_write
	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
};

static int pa2_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	/* register the device */
	printk(KERN_ALERT "module initialized :) :) :)");
device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	register_chrdev(333, "/dev/pa2_char_driver", &pa2_char_driver_file_operations);
	
	return 0;
}

static void pa2_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
	printk(KERN_ALERT "module bye bye");
	
	if(device_buffer){
	kfree(device_buffer);
	}
unregister_chrdev(333, "/dev/pa2_char_driver");
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);

