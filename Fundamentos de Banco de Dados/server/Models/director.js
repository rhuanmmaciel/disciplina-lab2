
const { DataTypes } = require('sequelize');
const db = require('./db');


const Director = db.sequelize.define('director', {
    directorId: {
      type: DataTypes.INTEGER,
      allowNull: false,
      primaryKey: true
    },
    directorName: {
      type: DataTypes.TEXT,
      allowNull: false
    },
    directorSex: {
      type: DataTypes.STRING(1),
      allowNull: true
    }
  }, {
    sequelize: db.sequelize, 
    tableName: 'director',
    timestamps: false,
    indexes: [
      {
        name: "PRIMARY",
        unique: true,
        using: "BTREE",
        fields: [
          { name: "directorId" },
        ]
      },
    ]
  });
  module.exports = Director;

