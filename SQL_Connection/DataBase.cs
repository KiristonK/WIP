using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace SQL_Connection
{
    class DataBase
    {
        private MySqlConnection connection = new MySqlConnection("server = 150.254.210.3");
    } 
}
