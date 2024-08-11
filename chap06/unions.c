
enum utype_enum {UT_INT, UT_FLOAT, UT_STRING};

union u_tag {
    int ival;
    float fval;
    char *sval;
} u;

int main() {
    enum utype_enum utype;

    if (utype == UT_INT)
        printf("%d\n", u.ival);
    if (utype == UT_FLOAT)
        printf("%f\n", u.fval);
    if (utype == UT_STRING)
        printf("%s\n", u.sval);
    else
        printf("bad type %d in utype\n", utype);
}