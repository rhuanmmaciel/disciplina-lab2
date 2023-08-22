const { DataTypes } = require('sequelize');
const Cast = require('../Models/cast.js');
const db = require('./db');

const Movie = db.sequelize.define('movie', {
  directorId: {
    type: DataTypes.INTEGER,
    allowNull: true,
    references: {
      model: 'director',
      key: 'directorId'
    }
  },
  genre: {
    type: DataTypes.TEXT,
    allowNull: false
  },
  gross: {
    type: DataTypes.TEXT,
    allowNull: true
  },
  IMDBRating: {
    type: DataTypes.FLOAT,
    allowNull: false
  },
  noOfVotes: {
    type: DataTypes.INTEGER,
    allowNull: false
  },
  overview: {
    type: DataTypes.TEXT,
    allowNull: false
  },
  releasedYear: {
    type: DataTypes.TEXT,
    allowNull: false
  },
  runtime: {
    type: DataTypes.TEXT,
    allowNull: false  
  },
  title: {
    type: DataTypes.TEXT,
    allowNull: false
  },
  movieId: {
    type: DataTypes.INTEGER,
    allowNull: false,
    primaryKey: true
  },
  poster: {
    type: DataTypes.TEXT,
    allowNull: false
  }
}, {
  sequelize: db.sequelize, 
  tableName: 'movie',
  timestamps: false,
  indexes: [
    {
      name: "PRIMARY",
      unique: true,
      using: "BTREE",
      fields: [
        { name: "movieId" },
      ]
    },
    {
      name: "directorId",
      using: "BTREE",
      fields: [
        { name: "directorId" },
      ]
    },
  ]
});

module.exports = Movie;
