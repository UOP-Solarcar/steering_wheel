#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

int main() {
    const char *dev_path = "/dev/input/js0";
    struct libevdev *dev = nullptr;
    int fd = open(dev_path, O_RDONLY);
    if (fd < 0) {
        std::cerr << "Failed to open " << dev_path << std::endl;
        return 1;
    }

    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        std::cerr << "Failed to init libevdev device" << std::endl;
        close(fd);
        return 1;
    }

    do {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc == 0 && ev.type == EV_KEY && ev.value == 1) {
            std::cout << "Button " << ev.code << " pressed" << std::endl;
        }
    } while (rc == 1 || rc == 0 || rc == -EAGAIN);

    libevdev_free(dev);
    close(fd);
    return 0;
}

