const { DataTypes } = require('sequelize');
const db = require('./db');
const Cast = require('../Models/cast.js');

const Actor = db.sequelize.define('actor', {
    actorID: {
      type: DataTypes.INTEGER,
      allowNull: false,
      primaryKey: true
    },
    country: {
      type: DataTypes.TEXT,
      allowNull: true
    },
    dateOfBirth: {
      type: DataTypes.TEXT,
      allowNull: true
    },
    ethnicity: {
      type: DataTypes.TEXT,
      allowNull: true
    },
    actorSex: {
      type: DataTypes.TEXT,
      allowNull: true
    },
    height: {
      type: DataTypes.TEXT,
      allowNull: true
    },
    actorName: {
      type: DataTypes.TEXT,
      allowNull: false
    },
    netWorth: {
      type: DataTypes.TEXT,
      allowNull: true
    }
  }, {
    sequelize: db.sequelize, 
    tableName: 'actor',
    timestamps: false,
    indexes: [
      {
        name: "PRIMARY",
        unique: true,
        using: "BTREE",
        fields: [
          { name: "actorID" },
        ]
      },
    ]
 
  });
  

  module.exports = Actor;
