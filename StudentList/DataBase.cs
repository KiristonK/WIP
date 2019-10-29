using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Npgsql;

namespace StudentList
{
    class DataBase
    {
        private readonly NpgsqlConnection _connection;
        private NpgsqlDataReader _dataReader;
        private NpgsqlCommand _cmd;

        public DataBase()
        {
            _connection = new NpgsqlConnection(
            @"Server=150.254.210.3; Port=5432; User Id=sbd24055; Password=sbd24055; Database=sbd_2019_20_z_db");
        }

        public void OpenConnection()
        {
            _connection.Open();
        }

        public bool CheckInDataBase(string user, string password)
        {
            _cmd = new NpgsqlCommand(
                $"SELECT * FROM sbd24055.\"usersList\" WHERE \"user\" LIKE '{user}' AND \"password\" LIKE '{password}'", _connection);
            _dataReader = _cmd.ExecuteReader();
            if (!_dataReader.Read())
            {
                _dataReader.Close();
                return false;
            }
            _dataReader.Close();
            return true;
        }
    }
}
