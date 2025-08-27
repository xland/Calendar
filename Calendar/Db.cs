using System;
using System.IO;
using Microsoft.Data.Sqlite;

namespace Calendar;

public class Db
{
    private SqliteConnection _connection;
    private static readonly Lazy<Db> _instance = new(() => new Db());
    public static Db Instance => _instance.Value;
    
    public Db()
    {
        initDb();
    }

    private void initDb()
    {
        string dbPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
        dbPath = Path.Combine(dbPath, "Calendar");
        Directory.CreateDirectory(dbPath);
        dbPath = Path.Combine(dbPath, "db.db");
        _connection = new SqliteConnection($"Data Source={dbPath}");
        _connection.Open();
        
        using var command = _connection.CreateCommand();
        command.CommandText = @"PRAGMA journal_mode = WAL;
CREATE TABLE Schedule(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL,Schedule TEXT,IsExpire INT,RepeatType INT,CreateTime BIGINT,FirstTime BIGINT,UpcomingTime BIGINT,Year INT,Month INT,Day INT,Time INT);
CREATE INDEX Schedule_Index ON Schedule(Schedule);
CREATE TABLE Setting(X INT,Y INT,AlertBefore INT,UpcomingNum INT);
INSERT INTO Setting(X,Y,AlertBefore,UpcomingNum) VALUES (999999,999999,5,3);";
        command.ExecuteNonQuery();
    }

    public void Exec(string sql)
    {
        using var command = _connection.CreateCommand();
        command.CommandText = sql;
        command.ExecuteNonQuery();
    }
    
    public void Dispose()
    {
        _connection.Close();
        _connection.Dispose();
    }
}