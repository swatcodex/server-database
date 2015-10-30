#include <mysql.h>
#include <stdio.h>
int main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *server = "localhost";
   char *user = "root";
   char *password = ""; /* set the server passwor */
   char *database = "sensorDB";
   conn = mysql_init(NULL);
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   /* send SQL query */
   if (mysql_query(conn, "select at.application_url from application_table at, device_app_assoc d where d.device_id=1 and d.application_id = at.application_id")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   printf("Application urls for the device are:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);
	  /* send SQL query */
   if (mysql_query(conn, "select flag from device_app_assoc where device_id=1")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   printf("Flag of url:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
   return 0;
}
